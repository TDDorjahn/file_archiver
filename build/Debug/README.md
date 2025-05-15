Debug Build:
- Select Debug Variant:
    * CMake Tools: Ctrl+Shift+P > CMake: Select Variant > Debug
    * Without CMT: create cmake-variants.yaml in root or IDE subdirectory for the project (for vscode, project subdirectory is .vscode/)

```
cd build/Debug
cmake ../..
cmake --build . --config Debug
```

Running Debug Build:
- With vscode:
    - Go to Debugger side panel
    - From the Run and Debug dropdown menu, select desired build type.
        *Note: Debug builds needs to run on (Debug) from the Run and Debug menu.
    - Click the "Start Debugging" button or press F5.
    - If the build matches the launch configuration, Release shouldn't debug, but Debug will.

* Note: If you just selected the Debug variant, running cmake ../.. in build/Debug is redunant, but is needed for each project structure change.