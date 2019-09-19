# Linux SGX Trust Management Framework
## Introduction
Trust Management Framework (or TruCE for short - "Trust in Cloud Enclaves") handles all aspects of remote attestation and secret delivery process in Intel SGX enclaves. The framework enables application developers to focus on the application code, performing attestation by a simple API call. Additional calls are available for easy-to-use enclave sealing and secret passing to enclaves.

Trust Management Framework is a service model that can have different implementations underneath, yet exposes the same interface to applications. The current implementation of remote attestation is based on the generation of an initial secret inside the enclave, instead of sending it to the enclave. We generate an RSA private/public key pair and embed the public key (hash) in the enclave attestation quote. Since the quote is signed by Intel keys, the resulting attestation report can be kept in an untrusted storage, reducing the trust requirements placed on TruCE server. The application clients can verify an enclave report by using the Intel attestation public key, retrieve the enclave public key and use it for the encryption of secrets (such as data keys) to be sent to the enclave for subsequent decryption and processing of sensitive data.

Trust Management Framework has two main components:

* TruCE server: A standalone process that registers with Intel Attestation Service and assists in remote attestation of RestAssured platform enclaves.
* TruCE SDK: A toolkit for application development. It has API and libraries for trusted (enclave) part of the cloud application, untrusted part of the cloud application, and the off-cloud client code that interacts with the cloud application.

Trust Management Framework can run in either real or simulated IAS mode. In the former, full remote attestation is performed, including the required interaction with the Intel Attestation Service (IAS). At a development stage, you can use the simulated IAS mode - there, TruCE doesnt need registration with Intel, since it doesnt contact the IAS and skips the attestation report signature verification step.


## Third party dependencies
* Download and install the latest packages of Intel SGX LINUX from https://01.org/intel-software-guard-extensions/downloads.
* Download and build SSL SGX located at the git repository https://github.com/intel/intel-sgx-ssl.
* Update the values of SGX_SDK and SSL_SGX in the Makefile.
* Download cpp-base64 from the git repository https://github.com/ReneNyffenegger/cpp-base64, and put the cpp-base64 folder under the aux_lib folder.
* Install the following packages:
	- sudo apt-get install libssl-dev
	- sudo apt-get install libjsoncpp-dev
	- sudo apt-get install libcurl4-openssl-dev
* In order to run the code in a real IAS mode, create a [developer account](https://software.intel.com/en-us/sgx). After the registration with a certificate (can be self-signed for development purposes), Intel will
respond with a SPID. Update defs.h with your SPID, certificate and the quote signing type.
* Following Revision 5 of Intel IAS API version 3, subscription keys are required to be sent in header of SigRL request. You can get yours [here](https://api.portal.trustedservices.intel.com/). After getting the keys, update defs.h with your latest SPID and put the keys global vars `subscription_key_p` and `subscription_key_p` in IAS_web_service.cpp with your primary and secondary subscription keys, respectively.

## Build
* In order to build in a simulated IAS mode, run "make SIMULATE_IAS=1".
* In order to build in a real IAS mode, run "make".
* A successful compilation should produce the following files:
	- Under application: libtruce_u.so, libtruce_t.a (and app).
	- Under client: libtruce_client.so (and client).
	- Under service-provider: truce_server.

## Usage
* Application:
	- The untrusted part should use the API in truce_app/truce_u.h and link with libtruce_u.so
	- The trusted part should import truce_enclave.edl, use the API in truce_enclave/truce_t.h  and link with libtruce_t.a
	- The file truce_enclave/truce_enclave_private.pem should be replaced with your enclave signing key (see SGX SDK documentation).
	- The file truce_enclave/truce_enclave.config.xml could be modified to configure the enclave memory size and other parameters.
	- truce_app/app.cpp is an example of the untrusted part of such application.
* Client:
	- Should use the API in truce_client.h and link with libtruce_client.so
	- client.cpp is an example of such a client.
* Service-Provider:
	- Run the truce_server executable


## Running the samples

1. Start the Truce server:

    ```sh
    cd /path-to/sgx-trust-management/service_provider
    ./truce_server
    ```

2. In a separate window, run the sample application:

    ```sh
    export LD_LIBRARY_PATH=/path-to/sgx-trust-management/application
    source sgxsdk/environment # from SGX SDK install directory
    cd /path-to/sgx-trust-management/application
    #Truce server address
    ./app 127.0.0.1
    ```

3. In a separate window, run the client:

    ```sh
    export LD_LIBRARY_PATH=/path-to/sgx-trust-management/client
    cd /path-to/sgx-trust-management/client
    ./client 127.0.0.1 
    ```

## Contact
Feel free to write to Gidon Gershinsky (gidon@il.ibm.com) and Eliad Tsfadia (eliad.tsfadia@ibm.com).
