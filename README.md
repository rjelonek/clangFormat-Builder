# clangFormat-Builder

## Purpose

The goal of this project is to make possible to use clang-format directly from IDE. With it you can easily introduce coding style rules. You can use existing style or make your own.

![concept](/assets/readme/concept.gif)

## Getting Started

### Prerequisites

To use `clangFormat-Builder` you need to install [clang-format](https://releases.llvm.org/download.html) tool. Also, you can find llvm project at [GitHub](https://github.com/llvm/llvm-project).

### Installation

#### Via GitHub

1. Download packaged binaries from the [releases page](https://github.com/rjelonek/clangFormat-Builder/releases)
2. Add to components via `Components->Install Packages`

#### Build from source

1. Open project in your IDE (you can find project file at `build/cXX`, where XX is version of C++Builder)
2. Build and install

> At `build` folder are only projects for C++Builder XE7 and 10.3. If you use another version just open one of existing projects.

## Usage

After installation you need set up the path of `clang-format.exe`, unless you added this path to environment variable `PATH`.

:warning: After formatting you lose your breakpoints at formatted file

:information_source: After formatting your bookmarks will be restored to previous lines

:information_source: Format operation can be undo

:information_source: Formatting or converting apply only for files with extension `*.h`, `*.hpp`, `*.cpp` and `*.cc`

:information_source: Settings are saved at `%APPDATA%/clangFormat/app.ini`

### Format on save

By default this feature is enabled. It is set up to use custom style without fallback style. To disable this feature press `Alt + D` or use menu `clangFormat->Enable auto formatting` or via settings form.

### Format on demand

When you want format your current source file on demand then press `Alt + A` or go to menu `clangFormat->Format current source`.

### Assign keyboard shortcuts

You can change default shortcuts for `Enable auto formatting` and `Format current source`.

### Other features
* format selected lines
* format all sources added to project
* convert file encoding to UTF-8 BOM

## Screenshots

![autoformatting](/assets/readme/autoformatting.gif)
![formattingOnDemand](/assets/readme/formattingOnDemand.gif)

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## Versioning

**RELEASE.BREAKING.FEATURE.FIX**

You can read about explicit versioning [here](https://medium.com/sapioit/why-having-3-numbers-in-the-version-name-is-bad-92fc1f6bc73c). Also, you can find information about similar software versioning schema [here](https://github.com/software-development-guidelines/explicit-versioning/blob/master/VERSIONING.md) and [here](https://github.com/exadra37-versioning/explicit-versioning).

## License

This project is licensed under the `Apache-2.0 License`. See the [LICENSE](/LICENSE) file for the full license text.

Copyright 2020 Rafał Jelonek