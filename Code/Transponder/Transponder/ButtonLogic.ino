void CheckForButtonPress() {
	LeftButtonState = digitalRead(LeftButton);
	RightButtonState = digitalRead(RightButton);
	SelectButtonState = digitalRead(SelectButton);

	if (LeftButtonState == HIGH) {
		switchDisplayState(false);
		delay(500);
	}

	if (RightButtonState == HIGH) {
		switchDisplayState(true);
		delay(500);
	}

	if (SelectButtonState == HIGH) {
		ChangeCubesatMode();
		delay(500);
	}
}