import mirage as mi
import numpy as np
import torch
import argparse

if __name__ == "__main__":
    parser.add_argument('--bs', type=int, default=1)
    parser.add_argument('--file', type=str, default='moe.json')
    args = parser.parse_args()
    batch_size = args.bs
    filename = args.file

    graph = mi.new_kernel_graph()
    X = graph.new_input(dims=(8, 8, 4096), dtype=mi.float16)
    A = graph.new_input(dims=(8, 4096, 4096), dtype=mi.float16)
    B = graph.new_input(dims=(8, 4096, 4096), dtype=mi.float16)
    D = graph.matmul(X, A)
    E = graph.exp(D)
    O = graph.matmul(E, B)
    graph.mark_output(O)
    optimized_graph = graph.superoptimize(previous_checkpoint="attention")

    input_tensors = [
        torch.randn(8, 8, 4096, dtype=torch.float16, device='cuda:0'),
        torch.randn(8, 4096, 4096, dtype=torch.float16, device='cuda:0'),
        torch.randn(8, 4096, 4096, dtype=torch.float16, device='cuda:0')
    ]

    for _ in range(16):
        optimized_graph(inputs=input_tensors)

    torch.cuda.synchronize()
    starter, ender = torch.cuda.Event(enable_timing=True), torch.cuda.Event(enable_timing=True)
    starter.record()
    for _ in range(1000):
        optimized_graph(inputs=input_tensors)
    ender.record()
    torch.cuda.synchronize()
    curr_time = starter.elapsed_time(ender)
    mean_syn = curr_time / 1000

    print("Best muGraph run time (ms): ", mean_syn)
