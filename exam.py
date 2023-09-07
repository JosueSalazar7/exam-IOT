import cv2
import cv2.aruco as aruco
import requests
import numpy as np

# Crear objeto detector de marcadores
parametros = aruco.DetectorParameters()

# Crear diccionario de marcadores aruco
aruco_diccionario = aruco.getPredefinedDictionary(aruco.DICT_6X6_250)

# Inicializar cámara
captura = cv2.VideoCapture(0, cv2.CAP_DSHOW)
#Cargar contenido virtual
nueva_imagen=cv2.imread("C:/Users/josue/OneDrive/Escritorio/exam IOT/AB043.jpg")
# Datos de Blynk
token = "1Z0BrTiNhGuEo8BOZstDT7jF7ma2a6qT"
pin_virtual = 'V5'
blynk_api_url = f'https://blynk.cloud/external/api/get?token={token}&{pin_virtual}'

while True:
    response = requests.get(blynk_api_url)
    valor = response.text

    # Capturar un cuadro de la cámara
    # Variable lectura: booleano indica si la lectura del cuadro fue exitosa
    lectura, frame = captura.read()

    # Convertir frame a escala de grises
    cuadro_gris = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Crear objeto detector ARuco
    detector = aruco.ArucoDetector(aruco_diccionario, parametros)

    # Detectar marcadores
    esquinas, identificador, puntosRechazados = detector.detectMarkers(cuadro_gris)

    if identificador is not None:
        # Dibujar el id sobre el marcador
        aruco.drawDetectedMarkers(frame, esquinas, identificador)

        for i in range(len(identificador)):
            # Obtener las esquinas del marcador actual
            marker_corners = esquinas[i][0]

            # Definir la posición y el tamaño del rectángulo
            x, y, w, h = cv2.boundingRect(marker_corners)

            # Dibujar un rectángulo alrededor del marcador
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

            # Mostrar el valor de Blynk en el cuadro
            cv2.putText(frame, "Sensor: " + valor, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)

    # Mostrar el resultado
    cv2.imshow('Ventana 1', frame)

    # Salir
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Liberar cámara y cerrar ventana
captura.release()
cv2.destroyAllWindows()
