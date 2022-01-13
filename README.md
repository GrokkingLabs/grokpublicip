# Introduction
This is a service to get the public IP of the service that is calling it.

# Building
## Pre-requisite
- CMake
- C++17 supported compiler or above
- make
- uSockets library (Clone the library and then execute make)
- Docker # in case you want to execute in the docker environment

## How to Build

### Building binary
- git clone https://github.com/GrokkingLabs/rabri.git rabri # Clone the repository 
- cd rabri # Go to the directory
- git submodule update --init --recursive # Initialize the submodules
- mkdir build # Create a build directory to store the build files
- cmake -H. -Bbuild -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release # Generate make files Unix systems
- make -C build # Build the project

### Building docker image
- docker build -t rabri . # You have to be in the build directory

## Executing

### Executing the binary
- ./build/rabri --port=8081 --threaded=1 # Start the server in the port mentioned
- nohup ./build/rabri --port=8081 --threaded=1 & # To start without shell associated
- docker run --name rabri -p 8080:8080 -d rabri
- cf push rabri -c './rabri' -b binary_buildpack -i 3 -k 256M -m 40M # Cloud Foundry

# Using the Endpoints

## / endpoint
This endpoint will give you the public ip
### Shell
#### Curl
```
curl --location --request GET 'http://grokkinglabs.xyz/'
```

#### Httpie
```
http --follow --timeout 3600 GET 'http://grokkinglabs.xyz/'
```

#### wget
```
wget --no-check-certificate --quiet \
  --method GET \
  --timeout=0 \
  --header '' \
   'http://grokkinglabs.xyz/'
```

### Python
#### requests
```
import requests

url = "http://grokkinglabs.xyz/"

payload={}
headers = {}

response = requests.request("GET", url, headers=headers, data=payload)

print(response.text)
```

### Javascript
#### Fetch
```
var requestOptions = {
  method: 'GET',
  redirect: 'follow'
};

fetch("http://grokkinglabs.xyz/", requestOptions)
  .then(response => response.text())
  .then(result => console.log(result))
  .catch(error => console.log('error', error));
  ```
  
#### JQuery
```
var settings = {
  "url": "http://grokkinglabs.xyz/",
  "method": "GET",
  "timeout": 0,
};

$.ajax(settings).done(function (response) {
  console.log(response);
});
```

#### XHR
```

var xhr = new XMLHttpRequest();
xhr.withCredentials = true;

xhr.addEventListener("readystatechange", function() {
  if(this.readyState === 4) {
    console.log(this.responseText);
  }
});

xhr.open("GET", "http://grokkinglabs.xyz/");

xhr.send();
```

### Java
#### OkHttp
```
OkHttpClient client = new OkHttpClient().newBuilder()
  .build();
Request request = new Request.Builder()
  .url("http://grokkinglabs.xyz/")
  .method("GET", null)
  .build();
Response response = client.newCall(request).execute();
```
