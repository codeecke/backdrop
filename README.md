# Backdrop-Steuerung

Dieses Projekt ist eine smarte Steuerung für meinen Studio-Hintergrund. Er erlaubt es den Papierhintergrund auf- und abzurollen, beliebige Positionen abzuspeichern und gezielt anzusteuern.

## Aktuelle Todos

### Frontend aufräumen

* [ ] Alle WebsocketEvents löschen, die aktuell nicht implementiert sind
* [ ] EventDispatcher durch eine CommandRegistry ersetzen (gleiche Logik wie im Backend)
* [ ] Geschwindigkeit (velocity) in MoveCommand und MoveToCommand implementieren

### Firmware
* [ ] PositionList 
	* [ ] speichern
	* [ ] laden
	* [ ] als FrontendCommand versenden
* [ ] MoveToCommand
* [ ] SavePositionCommand
* [ ] Aktuelle Position auf in regelmäßigen Abständen auf Änderung prüfen und bei update als FrontendCommand versenden
* [ ] Geschwindigkeit (velocity) in MoveCommand und MoveToCommand implementieren