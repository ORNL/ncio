param(
  [string]$step=""
)

# Run specific steps based on input

If($step -eq "configure")
{
  # Configure ncio using meson using out-of-source builds
  Write-Host "Start configuration"
  cd $Env:GITHUB_WORKSPACE\..
  mkdir ncio-build
  cd ncio-build
  C:\hostedtoolcache\windows\Python\3.9.1\x64\Scripts\meson.exe --prefix=$Env:GITHUB_WORKSPACE\..\ncio-install --default-library=static $Env:GITHUB_WORKSPACE
  Write-Host "End configuration"
}
ElseIf($step -eq "build")
{
  # Build using ninja
  cd $Env:GITHUB_WORKSPACE/../ncio-build
  ninja
}
ElseIf($step -eq "test")
{
  # Run all tests
  cd $Env:GITHUB_WORKSPACE/../ncio-build
  ninja -v test
  type D:\a\ncio\ncio-build\meson-logs\testlog.txt
}
ElseIf($step -eq "install")
{
  # Install the library
  cd $Env:GITHUB_WORKSPACE/../ncio-build
  ninja install
}
