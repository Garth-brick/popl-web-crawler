# Principles of Programming Languages - Group 23: Web Crawlers in C++ vs Rust

Created by:
- Vagarth Dvivedi (2021A7PS2426G)
- Vidit Kothari (2021A7PS2730G)
- Amit Kuvelker (2021A7PS3054G)

## Problem Statement

In the ever-evolving landscape of web technology, web crawling and scraping have become fundamental for various applications, from search engines to data analytics. The choice of programming language and implementation plays a crucial role in the efficiency and reliability of web crawlers. This project aims to compare two different web crawler implementations written in Rust and C++ to demonstrate the superior performance and reliability of the Rust implementation.

**For this project we have written all the code by ourselves. There are two implementations of the web crawler, one in C++ and another in Rust.**

### Project Uniqueness

Use of Curl Library in C++: Leveraging the Curl library in a C++ web crawler sets our project apart, as this library might not be commonly utilized in similar projects on platforms like GitHub.

Implementation of Multithreading in Rust: Employing multithreading in your Rust web crawler demonstrates a modern concurrency approach, showcasing the efficiency and parallelism that Rust can offer in web crawling applications.

Focus on Performance: Our project emphasizes performance optimizations, unique algorithms, or specific data structures tailored for crawling, highlight these aspects. These optimizations can set your project apart in terms of efficiency and speed.

Extensibility and Modularity: If your codebase emphasizes extensibility through a modular architecture, allowing easy addition of new functionalities or support for different protocols or formats, emphasize these design choices.

## POPL Concepts

### 1. Concurrency and Asynchronous Programming:

The Rust implementation utilizes asynchronous programming, allowing for efficient concurrent crawling of multiple URLs.

Rust:
```
// Asynchronous function
async fn get_html(url: String) -> Result<String, Box<dyn Error>> {
    let res = reqwest::get(&url).await?.text().await?;
    Ok(res)
```
C++:
```
// Synchronous function
std::string getHTML(const std::string& url) {
    // ...
}
```

### 2. Conciseness and Expressiveness:

Rust's syntax often allows for more concise and expressive code.

Rust:
```
let starting_url = "https://example.com".to_string();
```
C++:
```
std::string startingURL = "https://example.com"; // String manipulation in C++ is more verbose

```

### 3. Memory Safety and Ownership Model:

Rust's ownership model helps prevent memory-related bugs without the need for manual memory management.

Rust:
```
let mut urls = Vec::new(); // Ownership semantics
```
C++:
```
std::vector<std::string> urls; // Manual memory management
```

### 4. Concurrency with Channels:

Rust's channels provide a concise and safe way to handle concurrent operations.

Rust:
```
let (tx, mut rx) = mpsc::channel::<String>(100);
```
C++:
```
// Channels in C++ require more boilerplate code (e.g., std::queue, std::mutex, std::condition_variable)
```

### 5. Pattern Matching and Expressive Regex:

Rust's regex syntax can be more expressive and easier to read.

Rust:
```
let re = Regex::new(r#"<a href="(.*?)""#).unwrap();
```
C++:
```
std::regex url_regex("<a href=\"(.*?)\"");
```

### 6. Error Handling with Result Type:

Rust's Result type enforces explicit error handling, making it harder to ignore errors.

Rust:
```
async fn get_html(url: String) -> Result<String, Box<dyn Error>> {
    // ...
}
```
C++:
```
// Error handling often involves return codes or exceptions
```

### 7. Built-in Asynchronous Runtime (Tokio):

Rust's built-in asynchronous runtime (Tokio) simplifies asynchronous programming.

Rust:
```
#[tokio::main]
async fn main() -> Result<(), Box<dyn Error>> {
    // ...
}
```
C++:
```
// Asynchronous programming in C++ may require external libraries or more complex setups
```

### 8. Ownership and Borrowing:

Rust's ownership and borrowing system helps prevent data races and ensures memory safety.

Rust:
```
let url_clone = u.clone();
```
C++:
```
// Explicitly managing ownership and copying in C++
```

### 9. Concurrency with Async Recursion:

Rust's `async_recursion` attribute simplifies the implementation of asynchronous recursion.

Rust:
```
#[async_recursion]
async fn crawl(url: String, depth: i32, sender: mpsc::Sender<String>) -> Result<(), Box<dyn Error>> {
    // ...
}
```
C++:
```
// Implementing async recursion in C++ might require more complex setups
```


# Software Architecture Components

## C++ Web Crawler

This C++ program is a simple web crawler designed to retrieve and explore URLs from a given starting point up to a specified depth. It uses the libcurl library for making HTTP requests and regular expressions for extracting URLs from HTML content.

### Features

- **HTTP Requests:** Utilizes libcurl to perform HTTP GET requests and retrieve HTML content from a specified URL.

- **URL Extraction:** Employs regular expressions to extract URLs from the HTML content of webpages.

- **Recursion:** Implements a recursive crawling mechanism to explore URLs up to a specified depth.

### How to Use

1. **Dependencies:**
    - Ensure that you have the libcurl library installed. You can find it at [libcurl](https://curl.se/).

2. **Build:**
    - Compile the program using a C++ compiler. For example:
      ```bash
      g++ web_crawler.cpp -o web_crawler -lcurl
      ```

3. **Run:**
    - Execute the compiled program, providing the starting URL and maximum depth as command-line arguments.
      ```bash
      ./web_crawler <starting_url> <max_depth>
      ```

4. **Example:**
    ```bash
    ./web_crawler https://example.com 2
    ```

### Functions

#### `writeCallback`

This function handles the data received from the HTTP response. It appends the received content to a string and returns the size of the appended data.

#### `getHTML`

Retrieves the HTML content from a specified URL. It initializes a libcurl session, sets various options, performs the HTTP request, and returns the fetched HTML content.

#### `extractUrls`

Extracts URLs from the HTML content of a webpage using regular expressions. It searches for all matches of the URL pattern within the HTML content and stores them in a vector.

#### `crawl`

Recursively crawls through URLs up to a specified depth. It retrieves HTML content from the current URL, extracts URLs from it, and iterates through the extracted URLs. It then recursively calls itself to crawl deeper into the found URLs with reduced depth.

#### `main`

The main function initiates the web crawling process. It defines the starting URL and the maximum depth for traversal and calls the `crawl` function with these parameters to start the crawling process.

### Memory Management

There is no check for memory allocation failure when appending to the `readBuffer` in the `writeCallback` function. Consider adding a check for memory allocation failure. This is something that will never be allowed by the Rust compiler.

## Rust Web Crawler

This Rust program is a web crawler designed to asynchronously retrieve and explore URLs from a given starting point up to a specified depth. It uses the `reqwest` crate for making HTTP requests, `async_recursion` for asynchronous recursion, `regex` for pattern matching in HTML content, and `tokio` for handling asynchronous tasks.

### Features

- **Asynchronous Crawling:** Utilizes asynchronous programming with `async` and `await` for efficient crawling of multiple URLs concurrently.

- **HTTP Requests:** Utilizes the `reqwest` crate to perform HTTP GET requests and retrieve HTML content from a specified URL.

- **URL Extraction:** Employs regular expressions to extract URLs from the HTML content of webpages.

- **Recursive Crawling:** Implements asynchronous recursion to explore URLs up to a specified depth.

### How to Use

1. **Dependencies:**
    - Ensure that you have the necessary dependencies in your `Cargo.toml` file:
      ```toml
      [dependencies]
      reqwest = "0.11"
      async_recursion = "3.0"
      regex = "1.5"
      tokio = { version = "1", features = ["full"] }
      ```

2. **Build and Run:**
    - Compile and run the program using Cargo:
      ```bash
      cargo build
      cargo run
      ```

3. **Configuration:**
    - Replace the `starting_url` variable in the `main` function with your desired starting URL.
    - Define the `max_depth` variable to specify the maximum depth for traversal.

4. **Example:**
    ```rust
    #[tokio::main]
    async fn main() -> Result<(), Box<dyn std::error::Error>> {
        let starting_url = "https://example.com".to_string(); // Replace with the starting URL
        let max_depth = 2; // Define the maximum depth for traversal

        // ... (rest of the main function remains unchanged)
    }
    ```

### Functions

#### `get_html`

This asynchronous function retrieves the HTML content from a specified URL using the `reqwest` crate.

#### `extract_urls`

This function extracts URLs from the HTML content of a webpage using regular expressions. It searches for all matches of the URL pattern within the HTML content and stores them in a vector.

#### `crawl`

An asynchronous recursive function that crawls through URLs up to a specified depth. It fetches HTML content from the current URL, extracts URLs from it, and iterates through the extracted URLs. It then asynchronously calls itself to crawl deeper into the found URLs with reduced depth.

#### `main`

The main function initiates the web crawling process. It defines the starting URL and the maximum depth for traversal, then calls the `crawl` function with these parameters to start the crawling process.

### Error Handling

The code utilizes the `Result` type and the `?` operator for error propagation. However, additional error handling for channel sending operations in the `crawl` function could be considered.

### Concurrency

The code uses channels to send URLs to threads for crawling, providing a concurrent approach to the web crawling process.

# Results and Performance Analysis

## Performance Analysis using Instruments (MacOS):

**Objective:** Measure CPU usage and execution time comparison between Rust and C++ implementations of specific functionalities (e.g., HTTP request/response, URL parsing).

### Process:

Used the Instruments tool on MacOS to profile and measure CPU utilization for Rust and C++ code during execution.
Recorded and compared execution times for critical operations using Instruments' time profiler.

## Multi-threading Ease Comparison:

**Objective:** Assess the ease of implementing multi-threading in both Rust and C++.

### Rust Approach:

Leveraged Rust's std::thread and tokio or async-std libraries for asynchronous execution and multi-threading.
Compared the ease of managing concurrency, synchronization, and safety aspects in Rust.

### C++ Approach:

We attempted to do multi-threading in C++ but found the developer experience to be significantly worse because C++ is not thread-safe by default. We need to be ensuring thread-safety by manually setting up mutexes and locks while ensuring there are no memory leaks. 

## Findings and Observations:

### Performance Analysis Results:

Using Instruments for the Rust implemantion of the web crawler:

<img width="1440" alt="Screenshot 2023-11-20 at 10 57 06 PM" src="https://github.com/Garth-brick/popl-web-crawler/assets/92771830/17607ee5-b01e-4145-af89-7116fbed52fd">

Using Instruments for the C++ implemantion of the web crawler:

<img width="1440" alt="Screenshot 2023-11-20 at 10 58 09 PM" src="https://github.com/Garth-brick/popl-web-crawler/assets/92771830/cabc4fc3-5cfe-40da-9e35-21e3fa957a40">

Running the Rust web crawler which shows only **13%** CPU usage:

<img width="1438" alt="Screenshot 2023-11-20 at 11 27 54 PM" src="https://github.com/Garth-brick/popl-web-crawler/assets/92771830/a6f8479b-c06a-4d54-be78-664f74e8343d">

Running the C++ web crawler which shows a staggering **54%** CPU usage:

<img width="1435" alt="Screenshot 2023-11-20 at 11 30 43 PM" src="https://github.com/Garth-brick/popl-web-crawler/assets/92771830/9755f4ff-ffc6-498a-8072-4ba4659af828">


## Scope for Future Work  

### 1. **Optimizing HTTP Requests:**
   - **Connection Pooling:** Implement connection pooling to reuse existing connections for multiple requests, improving performance.

### 2. **Enhanced Asynchronous Handling:**
   - **Fine-Tuning Async Runtime:** Experiment with different async runtimes or configurations to find the optimal settings for your use case.

### 3. **Advanced Error Handling:**
   - **Detailed Error Reporting:** Provide more informative error messages, including the type of error and its context, for better debugging.

### 4. **Concurrency Improvements:**
   - **Thread Pooling:** Investigate the use of thread pools to parallelize certain non-async tasks and potentially improve overall throughput.

### 5. **Robust HTML Parsing:**
   - **HTML Parsing Library:** Consider using a dedicated HTML parsing library like `html5ever` for more robust URL extraction, handling various HTML structures.

### 6. **Rate Limiting:**
   - **Implement Rate Limiting:** To avoid overloading servers and adhere to ethical scraping practices, implement rate-limiting mechanisms.

### 7. **Security Considerations:**
   - **SSL/TLS Configuration:** Ensure secure communication by configuring SSL/TLS appropriately, especially if crawling websites with HTTPS.
