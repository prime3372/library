# arguments
$sol = $Args[0]
$gen = $Args[1]

g++ $sol -o sol.exe -O2 -std=c++23;
g++ $gen -o gen.exe -O2 -std=c++23;

for ($i = 1; $i -le 20; $i++) {
  python checker/interactive.py ".\\sol.exe" ".\\gen.exe"
  if ($LASTEXITCODE -ne 0) {
    Write-Host "Test" $i "WA"
    code in.txt out.txt
    break
  }
  Write-Host "Test" $i "AC"
}

Remove-Item sol.exe; Remove-Item gen.exe