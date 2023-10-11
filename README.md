# Exercise Backend C++
In this project the exercise shown in the 'docs' folder is solved. It consist on a C++ program capable of reading the meteorological data from the `csv` file in the 'data' folder, process it according to some request parameters and write the requested data in `json` format. An API created with the Python's library `FastAPI` has been developed to serve the data to a potential client in a more simple and convenient way.

## Data processing in C++
The C++ program in charge of reading and processing the data is in the 'main' folder. It consist on the `main.cpp` file, and two additional files containing the classes that implements the reading and processing of the file (`file_reading.cpp` and `file_processing.cpp`). Moreover, the nlohman's library for parsing json format (https://github.com/nlohmann/json) has been used. It can be found in the 'main/libs' folder.

The executable file created from the compilation of the code can be found in the 'main/build' folder under the name of `main.exe`. This program takes from 4 to 5 line arguments, in the following order: path to the csv file, city, temperature unit (C or F) and two dates in the format 'YYYY/MM/DD', being the second one optional. If only the first date is provided, the returned data wil consist of the entry corresponding to that date. If two dates are provided, the data corresponding to the time interval between both dates will be handed. Some examples of use as well the output json structure is:

```console
:~$ main.exe path/to/csv Valencia C 2023/10/03
{
    "city": "Valencia",
    "data": [
        {
            "T_max": 22.274999618530273,
            "date": "2023/10/03",
            "humidity": 0.0
        }
    ],
    "timestamp": 1697018112,
    "unit": "C"
}
```

```console
:~$ main.exe path/to/csv Madrid F 2023/10/03 2023/10/06
{
    "city": "Madrid",
    "data": [
        {
            "T_max": 52.25,
            "T_min": 42.45000076293945,
            "date": "2023/10/03",
            "humidity": 0.0
        },
        {
            "T_max": 52.849998474121094,
            "T_min": 42.54999923706055,
            "date": "2023/10/04",
            "humidity": 0.0
        },
        {
            "T_max": 53.95000076293945,
            "T_min": 43.25,
            "date": "2023/10/05",
            "humidity": 0.0
        },
        {
            "T_max": 53.45000076293945,
            "T_min": 43.650001525878906,
            "date": "2023/10/06",
            "humidity": 0.0
        }
    ],
    "timestamp": 1697035557,
    "unit": "F"
}
```

## Client's API
The API developed with FastAPI attends HTTP requests and calls the `main.exe` C++ executable with the propper arguments. The API consists on a sigle endpoint defined in the 'api/routes' folder: `/data/`. It handles only `GET` requests.

The requests parameters are specified as query parameters and they correspond to the same ones the executable file could take:

- **city** (string, required): The name of the city for which you want to retrieve data.

- **dateFrom** (string, required): The starting date of the data range. This should be in YYYY/MM/DD format.

- **dateTo** (string, optional): The ending date of the data range. If not provided, it defaults to an empty string.

- **unit** (string, optional): The temperature unit for the data. Defaults to "C" (Celsius) if not specified.

When the API recieves a request to the endpoint, it takes the query parameters and calls the C++ executable file in a subprocess. The steps to run the API server are the following ones:

1.  Create a virtual environment and install the necessary libraries using the `requirements.txt` file. This will mainly install the FastAPI library with the Uvicorn sever:

    ```Console
    :~$ python -m venv .venv
    ```
    ```Console
    :~$ pip install -r requirements.txt
    ```
2. Run the `main.py` file contained in the 'api' folder.
    ```Console
    :~$ python ./api/main.py
    ```
    From this point the API server will start listening to requests to http://127.0.0.1:8000.

The API will take the json output from the executable file and send it as a response. Some examples of possible URIs, that will get the data shown in previous section, are the following:

-   http://127.0.0.1:8000/data/?city=Valencia&dateFrom=2023/10/03

- http://127.0.0.1:8000/data/?city=Madrid&unit=F&dateFrom=2023/10/03&dateTo=2023/10/06


