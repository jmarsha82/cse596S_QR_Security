# CSE 569S Final Group Project - QR Code Walkthrough

## To test out Quirc's qrtest.c application
1.  Navigate to the "our_testing" directory
2.  Run the compiled qrtest using the following command:
```
./qrtest <pathtoimage> -d -v
```
## To perform fuzzing
3.  Once you have confirmed that the application runs you can perform an afl-fuzz by navigating to the "our_testing/tests" folder and run the following command (make sure the correct input image is available and that your output directory is empty):
```
afl-fuzz -i input/ -o output/ ./instrument_qrtest
```
4.  Once you have finished using afl-fuzz you have the option to run lib fuzz by navigating back one directory.
5.  Once you are back in the "our_testing" directory run the following command to start lib fuzz
```
./qrFuzzTest ./corpus -max_len=9000 -detect_leaks=0
```
*Note: A successful run of lib fuzz on qrtest was not accomplished during this evaluation*
