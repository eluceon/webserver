# Webserv: Lightweight HTTP Server in C++

## 📌 Overview

Webserver is a lightweight and customizable HTTP server crafted in C++.

## 🌟 Features

- **HTTP 1.1 Compliant**: Adheres to RFC 7230 to 7235 standards, ensuring a reliable and consistent web communication experience.

- **Supported Headers**: Includes a comprehensive set of HTTP headers for diversified use-cases, such as:
    - `Authorization`
    - `Content-Type`
    - `Date`
    - `Host`
    - `User-Agent`
    - ... and more.

- **Asynchronous Architecture**: Built with non-blocking I/O operations, ensuring rapid request-response cycles and optimized concurrency.

- **Dynamic Error Handling**: Offers a set of default error pages, but with the flexibility to customize as per application needs.

- **Configurability**: Comes with a dynamic configuration file system inspired by prominent web servers, enabling fine-tuning of server parameters.

- **Route Management**: Powerful routing mechanisms, allowing detailed specifications for resource handling and response generation.

- **CGI Execution**: Embedded support for CGI, making it adept in handling various file extensions and ensuring compatibility with platforms like php-cgi.

## ⚙️ Getting Started

### Installation

Ensure you're equipped with a C++ compiler and the essential libraries. Compile the server using:

```bash
make
