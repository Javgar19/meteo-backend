from fastapi import APIRouter
from pydantic import BaseModel
from pathlib import Path
import subprocess, json


router = APIRouter()

# Path to the project root
project_root = Path(__file__).resolve().parent.parent.parent

@router.get("/data/")
async def get_data(city: str, dateFrom: str, dateTo: str | None = "", unit: str | None = "C"):
    
    # Path to the executable file
    cpp_executable = project_root / "main" / "build" / "main.exe"

    # Path to the csv file
    csv_path = project_root / "data" / "Meteologica_vacante_Backend_developer_Prueba_Datos_20230927.csv"

    # Parameters to pass to the C++ executable
    cpp_parameters = str(csv_path) + " " + city + " " + unit + " " + dateFrom + " " + dateTo

    try:
        # Execute the C++ executable
        result = subprocess.run(str(cpp_executable) + " " + cpp_parameters, capture_output=True, text=True, check=True)

        # Get the output of the C++ executable
        output = result.stdout
        output_json = json.loads(output)

        return output_json
    
    except subprocess.CalledProcessError as e:
        return {"error": e.stderr}