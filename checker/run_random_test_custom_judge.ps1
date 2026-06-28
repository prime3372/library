#arguments
$sol = $Args[0]
$gen = $Args[1]
$judge = $Args[2]
$timelimit = $Args[3]
$timeout = $Args[4]

g++ $sol -o sol.exe -O2 -std=c++23
g++ $gen -o gen.exe -O2 -std=c++23
g++ $judge -o judge.exe -O2 -std=c++23

for ($i = 1; $i -le 20; $i++) {
  # run gen.exe
  $p_gen = Start-Process -FilePath .\gen.exe -RedirectStandardOutput in.txt -PassThru -WindowStyle Hidden
  $dummy = $p_gen.Handle
  if (-not $p_gen.WaitForExit($timeout)) {
    $p_gen.Kill()
    Write-Host "Test" $i "Failed:" "Time Out" $gen -ForegroundColor Blue
    code in.txt
    break
  }
  if ($p_gen.ExitCode -ne 0) {
    Write-Host "Test" $i "Failed:" "Runtime Error" $gen -ForegroundColor Blue
    code in.txt
    break
  }

  # run sol.exe
  $p_sol = Start-Process -FilePath .\sol.exe -RedirectStandardInput in.txt -RedirectStandardOutput out.txt -PassThru -WindowStyle Hidden
  $dummy = $p_sol.Handle
  $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
  if (-not $p_sol.WaitForExit($timeout)) {
    # time out
    $p_sol.Kill()
    Write-Host "Test" $i "TLE" ">" $timeout "ms" -ForegroundColor Yellow
    code in.txt out.txt
    break
  }
  $stopwatch.Stop()
  $time = $stopwatch.ElapsedMilliseconds

  # RE check
  if ($p_sol.ExitCode -ne 0) {
    Write-Host "Test" $i "RE" $time "ms" -ForegroundColor Magenta
    code in.txt out.txt
    break
  }

  # TLE check
  if ($time -gt $timelimit) {
    Write-Host "Test" $i "TLE" $time "ms" -ForegroundColor Yellow
    code in.txt out.txt
    break
  }

  # run judge.exe
  Get-Content "in.txt" | Set-Content "inout.txt"
  Get-Content "out.txt" | Add-Content "inout.txt"
  $p_judge = Start-Process -FilePath .\judge.exe -RedirectStandardInput inout.txt -PassThru -WindowStyle Hidden
  $dummy = $p_judge.Handle
  if (-not $p_judge.WaitForExit($timeout)) {
    $p_judge.Kill()
    Write-Host "Test" $i "Failed:" "Time Out" $judge -ForegroundColor Blue
    code in.txt out.txt
    break
  }

  # WA check
  if ($p_judge.ExitCode -ne 0) {
    Write-Host "Test" $i "WA" $time "ms" -ForegroundColor Red
    code in.txt out.txt
    break
  }

  Write-Host "Test" $i "AC" $time "ms" -ForegroundColor Green
}

Remove-Item sol.exe; Remove-Item gen.exe; Remove-Item judge.exe; Remove-Item inout.txt