import sys
import os
import time
import subprocess
import threading

# arguments
sol = sys.argv[1]
gen = sys.argv[2]
ans = sys.argv[3]
act = sys.argv[4]
che = sys.argv[5]
include = sys.argv[6]

# variables
timelimit = 5000
timeout = 10000
case_num = 50

# colors
CYAN = "\033[36m"
BLUE = "\033[34m"
YELLOW = "\033[33m"
MAGENTA = "\033[35m"
RED = "\033[31m"
GREEN = "\033[32m"
RESET = "\033[0m"

# results
OK = 0
WA = 1
PE = 2

def pump(src, dst, prefix, f_log):
    try:
        for line in src:
            f_log.write(prefix + line)
            f_log.flush()
            dst.write(line)
            dst.flush()
    except Exception:
        pass

def main():
    print("compiling...")

    opts = ["-I", include, "-O2", "-Wall", "-Wextra", "-fdiagnostics-color=always", "-std=c++23"]

    for src, exe in [(sol, "sol.exe"), (gen, "gen.exe"), (ans, "ans.exe"), (act, "act.exe"), (che, "che.exe")]:
        if subprocess.run(["g++", src] + opts + ["-o", exe]).returncode != 0:
            if os.path.exists(src):                
                subprocess.run(["code", src], shell=True)
            return

    print("compilation finished.")
    time.sleep(0.1)

    for i in range(1, case_num + 1):
        # run gen.exe
        try:
            with open("in.txt", "w") as f_in:
                subprocess.run(["./gen.exe"], stdout=f_in, timeout=timeout / 1000.0, check=True)
        except subprocess.TimeoutExpired:
            print(f"{BLUE}Test {i} FAIL Timed Out {gen}{RESET}")
            subprocess.run(["code", "in.txt"], shell=True)
            break
        except subprocess.CalledProcessError:
            print(f"{BLUE}Test {i} FAIL Runtime Error {gen}{RESET}")
            subprocess.run(["code", "in.txt"], shell=True)
            break

        # run ans.exe
        try:
            with open("in.txt", "r") as f_in, open("ans.txt", "w") as f_ans:
                subprocess.run(["./ans.exe"], stdin=f_in, stdout=f_ans, timeout=timeout / 1000.0, check=True)
        except subprocess.TimeoutExpired:
            print(f"{BLUE}Test {i} FAIL Timed Out {ans}{RESET}")
            subprocess.run(["code", "in.txt", "ans.txt"], shell=True)
            break
        except subprocess.CalledProcessError:
            print(f"{BLUE}Test {i} FAIL Runtime Error {ans}{RESET}")
            subprocess.run(["code", "in.txt", "ans.txt"], shell=True)
            break

        # run sol.exe
        p_sol = subprocess.Popen(["./sol.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
        p_act = subprocess.Popen(["./act.exe", "in.txt", "out.txt"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)

        with open("log.txt", "w") as f_log:
            t1 = threading.Thread(target=pump, args=(p_sol.stdout, p_act.stdin, "send    : ", f_log))
            t2 = threading.Thread(target=pump, args=(p_act.stdout, p_sol.stdin, "receive : ", f_log))
            t1.start()
            t2.start()

            start = time.perf_counter()
            tle = False
            while p_sol.poll() is None or p_act.poll() is None:
                if time.perf_counter() - start > timeout / 1000.0:
                    p_sol.kill()
                    p_act.kill()
                    tle = True
                    break
                time.sleep(0.01)

            t1.join()
            t2.join()

        t = int((time.perf_counter() - start) * 1000)

        if tle:
            print(f"{YELLOW}Test {i} TLE > {timeout} ms{RESET}")
            subprocess.run(["code", "in.txt", "log.txt", "out.txt", "ans.txt"], shell=True)
            break

        if p_sol.returncode != 0:
            print(f"{MAGENTA}Test {i} RE {t} ms{RESET}")
            subprocess.run(["code", "in.txt", "log.txt", "out.txt", "ans.txt"], shell=True)
            break

        if t > timelimit:
            print(f"{YELLOW}Test {i} TLE {t} ms{RESET}")
            subprocess.run(["code", "in.txt", "log.txt", "out.txt", "ans.txt"], shell=True)
            break

        if p_act.returncode != OK:
            if p_act.returncode == WA:
                print(f"{RED}Test {i} WA {t} ms{RESET}")
                subprocess.run(["code", "in.txt", "log.txt", "out.txt", "ans.txt"], shell=True)
                break
            elif p_act.returncode == PE:
                print(f"{RED}Test {i} PE {t} ms{RESET}")
                subprocess.run(["code", "in.txt", "log.txt", "out.txt", "ans.txt"], shell=True)
                break
            else:
                print(f"{BLUE}Test {i} FAIL Runtime Error {act}{RESET}")
                subprocess.run(["code", "in.txt", "log.txt", "out.txt", "ans.txt"], shell=True)
                break

        # run che.exe
        try:
            res = subprocess.run(["./che.exe", "in.txt", "out.txt", "ans.txt"], timeout=timeout / 1000.0)
            if res.returncode == OK:
                print(f"{GREEN}Test {i} AC {t} ms{RESET}")
            elif res.returncode == WA:
                print(f"{RED}Test {i} WA {t} ms{RESET}")
                subprocess.run(["code", "in.txt", "log.txt", "out.txt", "ans.txt"], shell=True)
                break
            elif res.returncode == PE:
                print(f"{RED}Test {i} PE {t} ms{RESET}")
                subprocess.run(["code", "in.txt", "log.txt", "out.txt", "ans.txt"], shell=True)
                break
            else:
                print(f"{BLUE}Test {i} FAIL Runtime Error {che}{RESET}")
                subprocess.run(["code", "in.txt", "log.txt", "out.txt", "ans.txt"], shell=True)
                break
        except subprocess.TimeoutExpired:
            print(f"{BLUE}Test {i} FAIL Timed Out {che}{RESET}")
            subprocess.run(["code", "in.txt", "log.txt", "out.txt", "ans.txt"], shell=True)
            break

if __name__ == "__main__":
    main()
    for f in ["sol.exe", "gen.exe", "ans.exe", "act.exe", "che.exe"]:
        if os.path.exists(f):
            os.remove(f)