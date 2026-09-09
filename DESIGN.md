# TinyKV Design

## Version 0: In-Memory KV Store

### Data Structure

All data will be stored in-memory using `std::unordered_map`.

- **Key**: `std::string` (must be non-empty)
- **Value**: `std::string` (can be empty)

### Interface

- `bool put(const std::string& key, const std::string& value)`: Insert or update a key-value pair. Returns `true` if the key is inserted or updated; returns `false` if the key is empty.
- `std::optional<std::string> get(std::string_view key) const`: Retrieves the value associated with the key, if it exists.
- `bool remove(std::string_view key)`: Deletes the key-value pair and returns `true` if the key exists.
- `bool exists(std::string_view key) const`: Checks for the presence of a key.

### Program Logic

Initialize system state -> Start main execution loop -> Read and parse user input -> Execute corresponding command -> Print result -> Repeat loop (Exit on certain command)

#### Commands

- `put KEY VALUE`
- `get KEY`
- `remove KEY`
- `contain KEY`

### Project Structure

- `main.cpp`: Entry point; runs the main execution loop and coordinates between modules.
- `command_parser.h`/`.cpp`: Parses raw input into structured commands.
- `kv_store.h`/`.cpp`: Implements the core key-value storage engine.
