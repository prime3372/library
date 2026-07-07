# arguments
$sol = $Args[0]
$gen = $Args[1]
$inc = $Args[2]

# constants
$timeout = 30000

do {
  Write-Host "compiling..."

  g++ $sol -I $inc -O2 -o sol.exe -std=c++23 -Wall -Wextra
  if ($LASTEXITCODE -ne 0) {
    Write-Host "Compile Error" -ForegroundColor Cyan
    if (Test-Path $sol) { code $sol }
    break
  }

  g++ $gen -I $inc -O2 -o gen.exe -std=c++23 -Wall -Wextra
  if ($LASTEXITCODE -ne 0) {
    Write-Host "FAIL" "Compile Error" $gen -ForegroundColor Blue
    if (Test-Path $gen) { code $gen }
    break
  }
  
  Write-Host "compilation is finished"

  Start-Sleep -Milliseconds 100 # Start-Sleep is necessary when compilation completes very quickly.

  # run gen.exe
  $p_gen = Start-Process -FilePath .\gen.exe -NoNewWindow -RedirectStandardOutput in.txt -PassThru
  $dummy = $p_gen.Handle
  if (-not $p_gen.WaitForExit($timeout)) {
    $p_gen.Kill()
    Write-Host "FAIL" "Timed Out" $gen -ForegroundColor Blue
    code in.txt
    break
  }
  if ($p_gen.ExitCode -ne 0) {
    Write-Host "FAIL" "Runtime Error" $gen -ForegroundColor Blue
    code in.txt
    break
  }

  # run sol.exe
  $p_sol = Start-Process -FilePath .\sol.exe -NoNewWindow -RedirectStandardInput in.txt -RedirectStandardOutput out.txt -PassThru
  $dummy = $p_sol.Handle
  $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
  if (-not $p_sol.WaitForExit($timeout)) {
    $p_sol.Kill()
    Write-Host "Timed Out" ">" $timeout "ms" -ForegroundColor Yellow
    code in.txt out.txt
    break
  }
  $stopwatch.Stop()
  $time = $stopwatch.ElapsedMilliseconds

  if ($p_sol.ExitCode -ne 0) {
    Write-Host "Runtime Error" $time "ms" -ForegroundColor Magenta
    code in.txt out.txt
    break
  }

  Write-Host "Success" $time "ms" -ForegroundColor Green
} while ($false)

Remove-Item sol.exe -ErrorAction SilentlyContinue
Remove-Item gen.exe -ErrorAction SilentlyContinue