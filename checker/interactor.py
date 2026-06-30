from enum import Enum
import sys
import subprocess
import threading

timeout_sec = 5
_ac = 0
_wa = 1
_re = 2
_tle = 3
_fail = 4

def pipe_stream(src, dst, log_file):
    with open(log_file, 'w', buffering=1) as f:
        for line in iter(src.readline, ''):
            if not line:
                break

            try:
                dst.write(line)
                dst.flush()
            except OSError:
                pass

            f.write(line)

def main():
    if len(sys.argv) < 3:
        sys.exit(_fail)

    cmd_gen = sys.argv[1]
    cmd_sol = sys.argv[2]

    p_gen = subprocess.Popen(cmd_gen, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    p_sol = subprocess.Popen(cmd_sol, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)

    t_in = threading.Thread(target=pipe_stream, args=(p_gen.stdout, p_sol.stdin, 'in.txt'))
    t_out = threading.Thread(target=pipe_stream, args=(p_sol.stdout, p_gen.stdin, 'out.txt'))

    t_in.start()
    t_out.start()

    try:
        p_sol.wait(timeout=timeout_sec)
    except subprocess.TimeoutExpired:
        sys.exit(_tle)

    t_out.join()

    try:
        p_gen.stdin.close()
    except Exception:
        pass

    p_gen.wait()
    t_in.join()

    if p_sol.returncode != 0:
        sys.exit(_re)

    if p_gen.returncode != 0:
        sys.exit(_wa)

    sys.exit(_ac)

if __name__ == '__main__':
    main()