# IoT TP 01: Node-RED, MQTT & NodeMCU

Built for the **ENSAM Casablanca** "Internet des Objets (IoT)" module.

This repository contains the implementations, Node-RED flows, and documentation for several IoT workshops.
It focuses on integrating hardware simulations (ESP32, sensors) with Node-RED dashboards using the MQTT protocol.

## Tech Stack

- **Hardware Simulation:** Wokwi (ESP32, DHT22, LDR, Servomotor)
- **Data Pipeline & UI:** Node-RED, MQTT (HiveMQ)
- **Documentation:** LaTeX

## Quick Start

> [!NOTE]
> Each workshop folder (`A15`, `A16-01`, `A16-02`) contains the Node-RED flow configuration (`flows.json`) and screenshots of the simulation.

### Wokwi Simulations

You can run the simulated environments directly in your browser:

- **Atelier 15:** [Open in Wokwi](https://wokwi.com/projects/462396191798252545)
- **Atelier 16 (Q1):** [Open in Wokwi](https://wokwi.com/projects/462396841658543105)
- **Atelier 16 (Q2):** [Open in Wokwi](https://wokwi.com/projects/462399698002882561)

### Node-RED Setup

1. Open your local or cloud Node-RED instance.
2. Go to **Menu > Import**.
3. Select the `flows.json` file from the specific workshop folder you want to test.
4. Deploy to see the dashboard in action.

---

<p align="center">Made with ❤️ by <a href="https://rabraghib.com/">Rabyâ Raghib</a>, Imane Saoudi, Nouhaila Nokry, Abdellah Moghandez & Mohamed Amane</p>
