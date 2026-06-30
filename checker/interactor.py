import sys
import subprocess
import threading

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
        sys.exit(4)

    cmd_gen = sys.argv[1]
    cmd_sol = sys.argv[2]
    timeout_sec = 5

    p_gen = subprocess.Popen(cmd_gen, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    p_sol = subprocess.Popen(cmd_sol, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)

    t_in = threading.Thread(target=pipe_stream, args=(p_gen.stdout, p_sol.stdin, 'in.txt'))
    t_out = threading.Thread(target=pipe_stream, args=(p_sol.stdout, p_gen.stdin, 'out.txt'))

    t_in.start()
    t_out.start()

    try:
        p_sol.wait(timeout=timeout_sec)
    except subprocess.TimeoutExpired:
        sys.exit(3)

    t_out.join()

    try:
        p_gen.stdin.close()
    except Exception:
        pass

    p_gen.wait()
    t_in.join()

    if p_sol.returncode != 0:
        sys.exit(2)

    if (p_gen.returncode != 0):
        sys.exit(1)

    sys.exit(0)

if __name__ == '__main__':
    main()