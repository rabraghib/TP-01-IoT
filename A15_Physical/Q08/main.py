import cv2
import mediapipe as mp
import math
import paho.mqtt.client as mqtt

# --- MQTT Configuration ---
MQTT_BROKER = "broker.hivemq.com"
MQTT_TOPIC = "IOT-G9/led"

client = mqtt.Client()
client.connect(MQTT_BROKER, 1883, 60)
client.loop_start()

# --- MediaPipe Configuration ---
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(min_detection_confidence=0.7, min_tracking_confidence=0.7)
mp_draw = mp.solutions.drawing_utils

cap = cv2.VideoCapture(0)
current_state = "off"

while True:
    success, img = cap.read()
    if not success:
        break

    # Mirror image for easier user interaction and conversion to RGB
    img = cv2.flip(img, 1)
    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

    # Détection
    results = hands.process(img_rgb)

    # Affichage des points et calcul de la distance
    if results.multi_hand_landmarks:
        for handLms in results.multi_hand_landmarks:
            mp_draw.draw_landmarks(img, handLms, mp_hands.HAND_CONNECTIONS)

            # Thumb tip = 4, Index finger tip = 8
            thumb_tip = handLms.landmark[4]
            index_tip = handLms.landmark[8]

            # Calculate Euclidean distance between the two points
            distance = math.hypot(index_tip.x - thumb_tip.x, index_tip.y - thumb_tip.y)

            # Pinch detection logic with hysteresis to prevent flickering
            new_state = current_state
            if distance < 0.05:  # Threshold for "pinch"
                new_state = "on"
            elif distance > 0.08:  # Threshold for "unpinch"
                new_state = "off"

            # Publish to HiveMQ ONLY if the state has changed
            if new_state != current_state:
                client.publish(MQTT_TOPIC, new_state)
                print(f"Message sent to {MQTT_TOPIC}: {new_state}")
                current_state = new_state

    cv2.imshow("Detection main", img)
    if cv2.waitKey(1) & 0xFF == 27:  # Press ESC to quit
        break

cap.release()
cv2.destroyAllWindows()
client.loop_stop()
client.disconnect()