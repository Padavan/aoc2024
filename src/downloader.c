// #include <stdio.h>
// #include <curl/curl.h>

// int download_file(void)
// {
//   CURL *curl;
//   CURLcode res;

//   curl = curl_easy_init();
//   if(curl) {
//     curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
//     /* example.com is redirected, so we tell libcurl to follow redirection */
//     curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

//     /* Perform the request, res gets the return code */
//     res = curl_easy_perform(curl);
//     /* Check for errors */
//     if(res != CURLE_OK)
//       fprintf(stderr, "curl_easy_perform() failed: %s\n",
//               curl_easy_strerror(res));

//     /* always cleanup */
//     curl_easy_cleanup(curl);
//   }
//   return 0;
// }

// int get_file(char filepath[]) {
//     bool file_exists (char *filepath) {
//     struct stat   buffer;

//     if (stat (filepath, &buffer) == 0) {
//         return 0;
//     } else {
//         download_file(filepath);
//     }

// }
