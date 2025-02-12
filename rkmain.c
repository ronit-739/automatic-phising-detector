int main() {
    char url[256], domain[256], decoded_domain[256];

    printf("Enter the URL: ");
    scanf("%255s", url);

    // Convert to lowercase
    for (int i = 0; url[i]; i++) {
        url[i] = tolower(url[i]);
    }

    // Extract domain from URL
    extract_domain(url, domain);

    // Decode any percent-encoded characters in domain
    url_decode(domain, decoded_domain);

    // Filter out special characters like '@'
    filter_special_chars(decoded_domain, '@');

    printf("Extracted Domain: %s\n", decoded_domain);  // Debugging Output

    // Read keywords from file
    char **keywords;
    int numkeywords = read_keywords_from_file("keywords.txt", &keywords);
    if (numkeywords < 0) {
        return 1;  // Exit if file reading fails
    }

    // Check for Punycode-encoded domains
    int punycode_detected = is_punycode_encoded(decoded_domain);
    if (punycode_detected) {
        printf("Warning! The domain contains Punycode-encoded characters. This could be a homograph attack.\n");
    }

    // Check for keyword-based phishing
    int suspicious_keywords_detected = keywordcontent(decoded_domain, keywords, numkeywords);
    if (suspicious_keywords_detected) {
        printf("Warning! The domain contains suspicious keywords.\n");
    }

    // Final decision
    if (punycode_detected || suspicious_keywords_detected) {
        printf("The URL is potentially malicious. Proceed with caution.\n");
    } else {
        printf("The URL seems safe based on current checks.\n");
    }

    // Free allocated memory for keywords
    for (int i = 0; i < numkeywords; i++) {
        free(keywords[i]);
    }
    free(keywords);

    return 0;
}