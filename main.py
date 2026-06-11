from fastapi import FastAPI
from fastapi.responses import FileResponse
from fastapi.staticfiles import StaticFiles
import paho.mqtt.publish as publish
import uvicorn

app = FastAPI()

BROKER = "192.168.0.4"
BROKER_GP3 = "192.168.0.114"
TOPICO_GP3 = "esp_led"
TOPICO = "Aula"
AUTH = {
    'username':'gp3',
    'password':'321'
}

app.mount("/static", StaticFiles(directory="web"), name="static")


@app.get("/")
def home():
    return FileResponse("web/index.html")


@app.post("/ligar")
def ligar():
    publish.single(
        TOPICO,
        "ON",
        hostname=BROKER,
        port=1883,
        auth=AUTH
    )

    return {"status": "LED ligado"}


@app.post("/desligar")
def desligar():
    publish.single(
        TOPICO,
        "OFF",
        hostname=BROKER,
        port=1883,
        auth=AUTH
    )

    return {"status": "LED desligado"}

#-----------------------------------------
@app.post("/ligar_gp3")
def ligar():
    publish.single(
        TOPICO_GP3,
        "ON",
        hostname=BROKER_GP3,
        port=1883,
        auth=AUTH
    )

    return {"status": "LED ligado"}

@app.post("/desligar_gp3")
def desligar():
    publish.single(
        TOPICO_GP3,
        "OFF",
        hostname=BROKER_GP3,
        port=1883,
        auth=AUTH
    )

    return {"status": "LED desligado"}



if __name__ == "__main__":
    import uvicorn

    uvicorn.run(
        "main:app",
        host="0.0.0.0",
        port=8000,
        reload=True
    )