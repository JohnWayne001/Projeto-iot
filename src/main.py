from fastapi import FastAPI
from fastapi.responses import FileResponse
from fastapi.staticfiles import StaticFiles
import paho.mqtt.publish as publish

app = FastAPI()

BROKER = "localhost"

app.mount("/static", StaticFiles(directory="src"), name="static")

@app.get("/")
def home():

    return FileResponse("src/index.html")

@app.post("/ligar")
def ligar():

    publish.single(
        "Aula",
        "ON",
        hostname=BROKER
    )

    return {"status":"LED ligado"}

@app.post("/desligar")
def desligar():

    publish.single(
        "Aula",
        "OFF",
        hostname=BROKER
    )

    return {"status":"LED desligado"}