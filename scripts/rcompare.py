import sys
import os
import time
import subprocess
import math

# arguments
gen = sys.argv[1]
sol = sys.argv[2]
ans = sys.argv[3]
max_error = float(sys.argv[4])
case_num = int(sys.argv[5])
include = sys.argv[6]

# variables
time_limit = 5000
opts = ["-I", include, "-O2", "-Wall", "-Wextra", "-fdiagnostics-color=always", "-std=c++23"]

def main():
    RESET = "\033[0m"
    RED = "\033[31m"
    GREEN = "\033[32m"
    YELLOW = "\033[33m"
    BLUE = "\033[34m"
    MAGENTA = "\033[35m"

    print("compiling...")

    targets = [(gen, "gen.exe"), (sol, "sol.exe"), (ans, "ans.exe")]

    procs = [subprocess.Popen(["g++", src] + opts + ["-o", exe]) for src, exe in targets]

    failed = False
    for p in procs:
        if p.wait() != 0 and not failed:
            failed = True

    if failed:
        print("compilation failed")
        return

    print("compilation finished")

    max_t = 0

    for i in range(1, case_num + 1):
        for f in ["in.txt", "out.txt", "ans.txt"]:
            try:
                os.remove(f)
            except Exception:
                pass

        # run gen.exe
        try:
            with open("in.txt", "w") as f_in:
                subprocess.run(["./gen.exe"], stdout=f_in, timeout=time_limit * 1.1 / 1000.0, check=True)
        except subprocess.TimeoutExpired:
            print(f"Test {i} {BLUE}Aborted{RESET} {gen} timed out")
            break
        except subprocess.CalledProcessError:
            print(f"Test {i} {BLUE}Aborted{RESET} {gen} returned a non-zero exit status")
            break

        # run sol.exe
        start = time.perf_counter()
        try:
            with open("in.txt", "r") as f_in, open("out.txt", "w") as f_out:
                subprocess.run(["./sol.exe"], stdin=f_in, stdout=f_out, timeout=time_limit * 1.1 / 1000.0, check=True)
        except subprocess.TimeoutExpired:
            print(f"Test {i} {YELLOW}Time Limit Exceeded{RESET} > {time_limit} ms")
            break
        except subprocess.CalledProcessError:
            t = math.ceil((time.perf_counter() - start) * 1000)
            print(f"Test {i} {MAGENTA}Runtime Error{RESET} {t} ms")
            break

        t = math.ceil((time.perf_counter() - start) * 1000)
        max_t = max(max_t, t)

        if t > time_limit:
            print(f"Test {i} {YELLOW}Time Limit Exceeded{RESET} > {time_limit} ms")
            break

        # run ans.exe
        try:
            with open("in.txt", "r") as f_in, open("ans.txt", "w") as f_ans:
                subprocess.run(["./ans.exe"], stdin=f_in, stdout=f_ans, timeout=time_limit * 1.1 / 1000.0, check=True)
        except subprocess.TimeoutExpired:
            print(f"Test {i} {BLUE}Aborted{RESET} {ans} timed out")
            break
        except subprocess.CalledProcessError:
            print(f"Test {i} {BLUE}Aborted{RESET} {ans} returned a non-zero exit status")
            break

        # compare out.txt and ans.txt
        with open("out.txt", 'r') as f_out, open("ans.txt", 'r') as f_ans:
            tokens_out = f_out.read().split()
            tokens_ans = f_ans.read().split()
            if len(tokens_out) != len(tokens_ans):
                print(f"Test {i} {RED}Wrong Answer{RESET} {t} ms")
                break            
            for t_out, t_ans in zip(tokens_out, tokens_ans):
                try:
                    f_out = float(t_out)
                    f_ans = float(t_ans)
                    if abs(f_out - f_ans) > max_error:
                        print(f"Test {i} {RED}Wrong Answer{RESET} {t} ms")
                        return
                except Exception:
                    if t_out != t_ans:
                        print(f"Test {i} {RED}Wrong Answer{RESET} {t} ms")
                        return
            print(f"Test {i} {GREEN}Passed{RESET} {t} ms")

if __name__ == "__main__":
    main()
    for f in ["sol.exe", "gen.exe", "ans.exe", "che.exe"]:
        if os.path.exists(f):
            try:
                os.remove(f)
            except Exception:
                pass