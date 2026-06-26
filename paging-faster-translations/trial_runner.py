import subprocess
import matplotlib.pyplot as plt

# NUM_PAGES_LIST = [2**x for x in range(1, 12)]  # 2, 4, 8, ..., 2048
NUM_PAGES_LIST = [2, 4, 8, 16, 32, 64, 128, 512, 1024]

NUM_TRIALS = 10_000_000

trial_times = []

for NUM_PAGES in NUM_PAGES_LIST:
    print(f"Running trial with {NUM_PAGES} pages...")
    result = subprocess.run(["./tlb.o", str(NUM_PAGES), str(NUM_TRIALS)], capture_output=True, text=True)
    print("Result:", result.stdout.strip())
    trial_times.append(float(result.stdout.strip()))

print("Trial times (ns):", trial_times)

plt.plot(NUM_PAGES_LIST, trial_times, marker='o')
plt.xscale('log', base=2)
plt.xlabel('Number of Pages (log scale)')
plt.ylabel('Time Taken (ns)')
plt.title('TLB Simulation Time vs Number of Pages')
plt.show()