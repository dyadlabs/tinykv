# TinyKV

TinyKV is a simple key-value storage system written in C++.

## Goals

TinyKV is a learning project for building a key-value store step by step.

## Current Scope

Version 0 provides an in-memory key-value store. Data is lost when the program exits.

## Features

- Put a key-value pair
- Get a value by key
- Remove a key-value pair by key
- Check whether a key exists

## Build

We use `cmake` to build the program.
```bash
cmake -S . -B build         # generate a makefile for building in the `build` directory
cmake --build build         # build the program to the `build` directory
```

## Usage

After building, you can use the program as follows.
```bash
./build/tinykv              # start the program in interactive mode by default
```
