from fastapi import FastAPI
import uvicorn
from routes import file_handler

app = FastAPI()

# Attach the route handlers to the FastAPI app
app.include_router(file_handler.router)

if __name__ == "__main__":
    uvicorn.run(app, host="127.0.0.1", port=8000)