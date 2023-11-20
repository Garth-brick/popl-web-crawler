 #include <iostream>
#include <curl/curl.h>
#include <vector>
#include <regex>

// Function to perform an HTTP GET request using cURL
size_t writeCallback(char* contents, size_t size, size_t nmemb, std::string* data) {
    // Appending the contents retrieved from the URL to a string
    data->append(contents, size * nmemb);
    return size * nmemb;
}

// Function to retrieve HTML content from a given URL
std::string getHTML(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    // Initialize cURL for making HTTP requests
    curl = curl_easy_init();
    if (curl) {
        // Set the URL to be requested
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // Enable following redirects
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        // Set the write callback function for handling the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        // Set the pointer to the string where the response will be stored
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        // Perform the HTTP request
        res = curl_easy_perform(curl);
        // Clean up cURL resources
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

// Function to extract URLs from the HTML content of a webpage
std::vector<std::string> extractUrls(const std::string& html) {
    std::vector<std::string> urls;
    std::regex url_regex("<a href=\"(.*?)\"");
    // Find all matches of the URL pattern in the HTML content
    std::sregex_iterator it(html.begin(), html.end(), url_regex);
    std::sregex_iterator end;
    for (; it != end; ++it) {
        std::smatch match = *it;
        // Add the matched URL to the vector of URLs
        urls.push_back(match.str(1));
    }
    return urls;
}

// Function to crawl through URLs recursively up to a certain depth
void crawl(const std::string& url, int depth) {
    if (depth <= 0) {
        return;
    }
    // Retrieve HTML content from the current URL
    std::string html = getHTML(url);
    // Extract URLs from the HTML content
    std::vector<std::string> urls = extractUrls(html);
    // Iterate through the extracted URLs
    for (const std::string &u : urls) {
        // Print the found URL 
        std::cout << "Found URL: " << u << std::endl;
        // Recursively crawl through the found URL with reduced depth
        crawl(u, depth - 1);
    }
}

// Main function to initiate the crawling process
int main() {
    // Define the starting URL for the web crawling process
    std::string startingURL = "https://google.com"; // Enter the starting URL here
    // Define the maximum depth for traversal
    int maxDepth = 1;

    // Initiate the crawling process with the specified parameters
    crawl(startingURL, maxDepth);

    return 0;
}


/*writeCallback: This function is responsible for handling the data received from the HTTP response. It appends the received content to a string and returns the size of the appended data.

getHTML: This function is used to retrieve the HTML content from a specified URL. It initializes a cURL session, sets various cURL options such as the URL, follows redirects, specifies the write callback function, and performs the HTTP request. It then cleans up the cURL resources and returns the fetched HTML content.

extractUrls: This function extracts URLs from the HTML content of a webpage using regular expressions. It searches for all matches of the URL pattern within the HTML content and stores them in a vector.

crawl: This function is responsible for crawling through URLs recursively up to a specified depth. It retrieves HTML content from the current URL, extracts URLs from it, and iterates through the extracted URLs. It then recursively calls itself to crawl deeper into the found URLs with reduced depth.

main: The main function initiates the web crawling process. It defines the starting URL and the maximum depth for traversal and calls the crawl function with these parameters to start the crawling process. */