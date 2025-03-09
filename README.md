# Backdrop-Steuerung

Dieses Projekt ist eine smarte Steuerung für meinen Studio-Hintergrund. Er erlaubt es den Papierhintergrund auf- und abzurollen, beliebige Positionen abzuspeichern und gezielt anzusteuern.

## Aktuelle Todos

### Frontend aufräumen

* [X] Alle WebsocketEvents löschen, die aktuell nicht implementiert sind
* [X] EventDispatcher durch eine CommandRegistry ersetzen (gleiche Logik wie im Backend)
* [ ] Geschwindigkeit (velocity) in MoveCommand und MoveToCommand implementieren

### Firmware
* [X] PositionList 
	* [X] speichern
	* [X] laden
	* [X] als FrontendCommand versenden
* [X] MoveToCommand
* [X] SavePositionCommand
* [ ] Aktuelle Position in regelmäßigen Abständen auf Änderung prüfen und bei update als FrontendCommand versenden
* [ ] Geschwindigkeit (velocity) in MoveCommand und MoveToCommand implementieren
* [ ] CalibrateCommand