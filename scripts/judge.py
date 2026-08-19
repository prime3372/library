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
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"
RESET = "\033[0m"

# results
OK = 0
WA = 1
PE = 2

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
            print(f"{BLUE}Test {i} Fail Timed Out {gen}{RESET}")
            break
        except subprocess.CalledProcessError:
            print(f"{BLUE}Test {i} Fail Runtime Error {gen}{RESET}")
            break

        # run ans.exe
        try:
            with open("in.txt", "r") as f_in, open("ans.txt", "w") as f_ans:
                subprocess.run(["./ans.exe"], stdin=f_in, stdout=f_ans, timeout=timeout / 1000.0, check=True)
        except subprocess.TimeoutExpired:
            print(f"{BLUE}Test {i} Fail Timed Out {ans}{RESET}")
            break
        except subprocess.CalledProcessError:
            print(f"{BLUE}Test {i} Fail Runtime Error {ans}{RESET}")
            break

        # run sol.exe
        start = time.perf_counter()
        try:
            with open("in.txt", "r") as f_in, open("out.txt", "w") as f_out:
                subprocess.run(["./sol.exe"], stdin=f_in, stdout=f_out, timeout=timeout / 1000.0, check=True)
            t = int((time.perf_counter() - start) * 1000)
        except subprocess.TimeoutExpired:
            print(f"{YELLOW}Test {i} TLE > {timeout} ms{RESET}")
            break
        except subprocess.CalledProcessError:
            t = int((time.perf_counter() - start) * 1000)
            print(f"{MAGENTA}Test {i} RE {t} ms{RESET}")
            break

        if t > timelimit:
            print(f"{YELLOW}Test {i} TLE {t} ms{RESET}")
            break

        # run che.exe
        try:
            res = subprocess.run(["./che.exe", "in.txt", "out.txt", "ans.txt"], timeout=timeout / 1000.0)
            if res.returncode == OK:
                print(f"{GREEN}Test {i} AC {t} ms{RESET}")
                subprocess.run(["cmd", "/c", "del", "in.txt", "out.txt", "ans.txt"])
            elif res.returncode == WA:
                print(f"{RED}Test {i} WA {t} ms{RESET}")
                break
            elif res.returncode == PE:
                print(f"{RED}Test {i} PE {t} ms{RESET}")
                break
            else:
                print(f"{BLUE}Test {i} Fail Runtime Error {che}{RESET}")
                break
        except subprocess.TimeoutExpired:
            print(f"{BLUE}Test {i} Fail Timed Out {che}{RESET}")
            break

if __name__ == "__main__":
    main()
    for f in ["sol.exe", "gen.exe", "ans.exe", "che.exe"]:
        if os.path.exists(f):
            os.remove(f)