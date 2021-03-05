del   out.txt
openssl rsautl -encrypt -in in.txt -inkey key.pem -pubin -out enc.txt 
openssl base64 -in enc.txt   > out.txt
