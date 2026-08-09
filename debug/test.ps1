# arguments
$sol = $Args[0]
$gen = $Args[1]
$include = $Args[2]

# constants
$timeout = 10000
$case_num = 20

do {
  Write-Host "compiling..."

  g++ $sol -I $include -O2 -Wall -Wextra -fdiagnostics-color=always -o sol.exe -std=c++23
  if ($LASTEXITCODE -ne 0) {
    Write-Host "Compile Error" -ForegroundColor Cyan
    if (Test-Path $sol) { code $sol }
    break
  }

  g++ $gen -I $include -O2 -Wall -Wextra -fdiagnostics-color=always -o gen.exe -std=c++23
  if ($LASTEXITCODE -ne 0) {
    Write-Host "FAIL" "Compile Error" $gen -ForegroundColor Blue
    if (Test-Path $gen) { code $gen }
    break
  }

  Write-Host "compilation finished"

  Start-Sleep -Milliseconds 100

  for ($i = 1; $i -le $case_num; $i++) {
    # run gen.exe
    $p_gen = Start-Process -FilePath .\gen.exe -NoNewWindow -RedirectStandardOutput in.txt -PassThru
    $p_gen.Handle | Out-Null
    if (-not $p_gen.WaitForExit($timeout)) {
      $p_gen.Kill()
      Write-Host "Test" $i "FAIL" "Timed Out" $gen -ForegroundColor Blue
      code in.txt
      break
    }
    if ($p_gen.ExitCode -ne 0) {
      Write-Host "Test" $i "FAIL" "Runtime Error" $gen -ForegroundColor Blue
      code in.txt
      break
    }

    # run sol.exe
    $p_sol = Start-Process -FilePath .\sol.exe -NoNewWindow -RedirectStandardInput in.txt -RedirectStandardOutput out.txt -PassThru
    $p_sol.Handle | Out-Null
    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    if (-not $p_sol.WaitForExit($timeout)) {
      $p_sol.Kill()
      Write-Host "Test" $i "Timed Out" ">" $timeout "ms" -ForegroundColor Yellow
      code in.txt out.txt
      break
    }
    $stopwatch.Stop()
    $time = $stopwatch.ElapsedMilliseconds

    if ($p_sol.ExitCode -ne 0) {
      Write-Host "Test" $i "Runtime Error" $time "ms" -ForegroundColor Magenta
      code in.txt out.txt
      break
    }

    Write-Host "Test" $i "Success" $time "ms" -ForegroundColor Green
  }

} while ($false)

Remove-Item sol.exe -ErrorAction SilentlyContinue
Remove-Item gen.exe -ErrorAction SilentlyContinue