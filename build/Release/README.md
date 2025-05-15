Release Build:
- Select Release Variant:
    * CMake Tools: Ctrl+Shift+P > CMake: Select Variant > Release
    * Without CMT: create cmake-variants.yaml in root or IDE subdirectory for the project (for vscode, project subdirectory is .vscode/)

```
cd build/Release
cmake ../..
cmake --build . --config Release
```

Running Release Build:
- With vscode:
    - Go to Debugger side panel
    - From the Run and Debug dropdown menu, select desired build type.
        *Note: Release builds needs to run on (Release) from the Run and Debug menu.
    - Click the "Start Debugging" button or press F5.
    - If the build matches the launch configuration, Release shouldn't debug, but Debug will.

* Note: If you just selected the Release variant, running cmake ../.. in build/Release is redunant, but is needed for each project structure change.