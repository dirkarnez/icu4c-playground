icu4c-playground
================
### Notes
- with reference to [c++ - How to link my app statically against ICU 57.1 MinGW - Stack Overflow](https://stackoverflow.com/questions/41143845/how-to-link-my-app-statically-against-icu-57-1-mingw)
- Windows console may not show Chinese characters properly - (**solution**: use `cmd.exe` with MingLiu font and `>` as output `.txt` file and view in notepad++ in "UTF-8" mode, no need to set "Character sets")

### TODOs
- [ ] Study `NumberPatterns4` in [ICU Demonstration - Locale Explorer](https://icu4c-demos.unicode.org/icu-bin/locexp?d_=en&_=zh_Hant_HK)
- [ ] CMake style import: `-DICU_ROOT="$workspace/icu4c-v71.1-x86_64-posix-seh-rev0-8.1.0"`
  - [FindICU — CMake 3.25.1 Documentation](https://cmake.org/cmake/help/latest/module/FindICU.html)
### Using
- [dirkarnez/icu4c-prebuilt](https://github.com/dirkarnez/icu4c-prebuilt)

### Documentation
- https://www.unicodeconference.org/presentations-43/TS1T3-Loomis-Carr.pdf
