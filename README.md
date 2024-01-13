# 🦣 Nominator

A simple application that could've just been a single line in bash, but instead is a full-blown application to study C++.

![License](https://img.shields.io/github/license/tacosontitan/nominator?logo=github&style=for-the-badge)

## 🐙 What does it do?

The application loads all subdirectories in the specified working directory and creates a `DirectoryWorker` for each subdirectory. Then, each `DirectoryWorker` renames all files in its working directory to `directory-n` where `n` is the index of the file being processed.