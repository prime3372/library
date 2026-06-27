g++ $Args[0] -o checker.exe -std=c++23
g++ $Args[1] -o sol.exe -O2 -std=c++23
g++ $Args[2] -o gen.exe -O2 -std=c++23
g++ $Args[3] -o ans.exe -O2 -std=c++23

for ($i = 1; $i -le 20; $i++) {
  cmd /c ".\\gen.exe > in.txt"
  if ($LASTEXITCODE -ne 0) {
    Write-Host "Test" $i "Fail"
    code in.txt
    break
  }

  cmd /c ".\\ans.exe < in.txt > ans.txt"
  if ($LASTEXITCODE -ne 0) {
    Write-Host "Test" $i "Fail"
    code in.txt ans.txt
    break
  }

  cmd /c ".\\sol.exe < in.txt > out.txt"
  if ($LASTEXITCODE -ne 0) {
    Write-Host "Test" $i "RE"
    code in.txt out.txt ans.txt
    break
  }

  ./checker.exe out.txt ans.txt
  if ($LASTEXITCODE -ne 0) {
    Write-Host "Test" $i "WA"
    code in.txt out.txt ans.txt
    break
  }
}

Remove-Item gen.exe; Remove-Item sol.exe; Remove-Item ans.exe; Remove-Item checker.exe