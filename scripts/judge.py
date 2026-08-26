import sys
import os
import time
import subprocess

# arguments
sol = sys.argv[1]
gen = sys.argv[2]
ans = sys.argv[3]
che = sys.argv[4]
include = sys.argv[5]

# variables
timelimit = 5000
timeout = 10000
case_num = 50
opts = ["-I", include, "-O2", "-Wall", "-Wextra", "-fdiagnostics-color=always", "-std=c++23"]

# colors
RESET = "\033[0m"
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"

# result code
OK = [0]
WA = [1, 2]

def main():
    print("compiling...")

    targets = [(sol, "sol.exe"), (gen, "gen.exe"), (ans, "ans.exe"), (che, "che.exe")]

    procs = [subprocess.Popen(["g++", src] + opts + ["-o", exe]) for src, exe in targets]

    failed = False
    for p in procs:
        if p.wait() != 0 and not failed:
            failed = True

    if failed:
        return

    print("compilation finished.")
    time.sleep(0.1)

    for i in range(1, case_num + 1):
        # run gen.exe
        try:
            with open("in.txt", "w") as f_in:
                subprocess.run(["./gen.exe"], stdout=f_in, timeout=timeout / 1000.0, check=True)
        except subprocess.TimeoutExpired:
            print(f"Test {i} {BLUE}Fail{RESET} Timed Out {gen}")
            break
        except subprocess.CalledProcessError:
            print(f"Test {i} {BLUE}Fail{RESET} Runtime Error {gen}")
            break

        # run ans.exe
        try:
            with open("in.txt", "r") as f_in, open("ans.txt", "w") as f_ans:
                subprocess.run(["./ans.exe"], stdin=f_in, stdout=f_ans, timeout=timeout / 1000.0, check=True)
        except subprocess.TimeoutExpired:
            print(f"Test {i} {BLUE}Fail{RESET} Timed Out {ans}")
            break
        except subprocess.CalledProcessError:
            print(f"Test {i} {BLUE}Fail{RESET} Runtime Error {ans}")
            break

        # run sol.exe
        start = time.perf_counter()
        try:
            with open("in.txt", "r") as f_in, open("out.txt", "w") as f_out:
                subprocess.run(["./sol.exe"], stdin=f_in, stdout=f_out, timeout=timeout / 1000.0, check=True)
            t = int((time.perf_counter() - start) * 1000)
        except subprocess.TimeoutExpired:
            print(f"Test {i} {YELLOW}TLE{RESET} > {timeout} ms")
            break
        except subprocess.CalledProcessError:
            t = int((time.perf_counter() - start) * 1000)
            print(f"Test {i} {MAGENTA}RE{RESET} {t} ms")
            break

        if t > timelimit:
            print(f"Test {i} {YELLOW}TLE{RESET} {t} ms")
            break

        # run che.exe
        try:
            res = subprocess.run(["./che.exe", "in.txt", "out.txt", "ans.txt"], timeout=timeout / 1000.0)
            if res.returncode in OK:
                print(f"Test {i} {GREEN}AC{RESET} {t} ms")
                if i != case_num:
                    subprocess.run(["cmd", "/c", "del", "in.txt", "out.txt", "ans.txt"])
            elif res.returncode in WA:
                print(f"Test {i} {RED}WA{RESET} {t} ms")
                break
            else:
                print(f"Test {i} {BLUE}Fail{RESET} Runtime Error {che}")
                break
        except subprocess.TimeoutExpired:
            print(f"Test {i} {BLUE}Fail{RESET} Timed Out {che}")
            break

if __name__ == "__main__":
    main()
    for f in ["sol.exe", "gen.exe", "ans.exe", "che.exe"]:
        if os.path.exists(f):
            os.remove(f)