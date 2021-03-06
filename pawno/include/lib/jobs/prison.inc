stock SetPlayerLaundryAnimations(playerid)
(
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY)
	SetPlayerAttachedObject(playerid, SLOT_TRYING, 1576, 6, 0.10, -0.030999, -0.155, -112.5, -5.89993, 88.1001, 1.0, 1.0, 1.0, 0xFFFF8C2C)
	return 1
)

stock SetPlayerWorkshopAnimations(playerid)
(
	hrp_TogglePlayerControllable(playerid, false)
	ApplyAnimation(playerid, SWORD, sword_IDLE, 4.1, 0, 0, 0, 1, 0, 1)
	return 1
)

stock StopPlayerAnimations(playerid)
(
	hrp_TogglePlayerControllable(playerid, true)
	ClearAnimations(playerid)
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE)
	RemovePlayerAttachedObject(playerid, SLOT_TRYING)
	return 1
)

stock StopPlayerPrisonWork(playerid)
(
	StopPlayerAnimations(playerid)
	
	PlayerCache(playerid)(pWorkingNow) = 0
	PlayerCache(playerid)(pWorkingPhase) = 0
)

CMD:praca(playerid, params())
(
	if(PlayerCache(playerid)(pBW))
	(
		GuiMsg(playerid, Nie mo�esz tego zrobi� b�d�c nieprzytomnym., 1)
		return 1
	)
	if(!PlayerCache(playerid)(pArrest))
	(
		GuiMsg(playerid, Tej komendy mo�esz u�y� do pracy tylko b�d�c w areszcie., 1)
		return 1
	)
	
	if(PlayerCache(playerid)(pWorkingNow))
	(
		GuiMsg(playerid, Pracowa�e�, obecnie przerwa�e� prac� w wi�zieniu., 0)
		StopPlayerPrisonWork(playerid)
		return 1
	)
	
	if(PlayerCache(playerid)(pWorkRepeat) )= 10)
	(
		GuiMsg(playerid, Wyczerpa�e� dzienny limit pracy, odpocznij., 0)
		return 1
	)
	
	type(32)
	if(sscanf(params, s(32), type))
	(
		hrp_Tip(playerid, /praca (pralnia | warsztat))
		return 1
	)
	
	// sprawdzanie limitu prac dziennych
	
	if(!strcmp(type, pralnia, true))
	(
		if(PlayerCache(playerid)(pWorkingNow))
		(
			GuiMsg(playerid, Obecnie pracujesz.\nAby przerwa� prac� u�yj komendy /praca., 1)
			return 1
		)
		if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1782.0901, -1548.1317, 40.8159))
		(
			GuiMsg(playerid, Aby rozpocz�� prac� w pralni musisz si� tam znajdowa�., 1)
			return 1
		)
		PlayerCache(playerid)(pWorkingNow) = WORK_LAUNDRY
		PlayerCache(playerid)(pWorkingPhase) = LAUNDRY_UNLOADED
		GuiMsg(playerid, Rozpocz��e� prac� jako pomocnik w pralni!\nTeraz musisz uda� si� do poszczeg�lnych cel aby zebra� brudn� odzie� wi�ni�w oraz prze�cierad�a z powrotem do pralni.\nB�d�c w celi aby podnie�� rzeczy u�yj klawisza H (klakson)., 0)
	)
	else if(!strcmp(type, warsztat, true))
	(
		if(PlayerCache(playerid)(pWorkingNow))
		(
			GuiMsg(playerid, Obecnie pracujesz.\nAby przerwa� prac� u�yj komendy /praca., 1)
			return 1
		)
		if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1764.4370, -1534.9044, 39.9441))
		(
			GuiMsg(playerid, Aby rozpocz�� prac� w warsztacie musisz znajdowa� si� przy stanowisku., 1)
			return 1
		)
		PlayerCache(playerid)(pWorkingNow) = WORK_WORKSHOP
		PlayerCache(playerid)(pWorkingPhase) = WORKSHOP_WAITING
		PlayerCache(playerid)(pWorkingRepeat) = 0
		GuiMsg(playerid, Rozpocz��e� prac� jako cie�la w warsztacie!\nAby rozpocz�� prac� u�yj klawisza H (klakson). Je�eli chcesz przerwa� prac� ponownie u�yj klawisza H.\nPo rozpocz�ciu pracy musisz w okre�lonym czasie wcisn�� wystarczaj�c� du�� ilo�� LPM (lewy przycisk myszki), stra�nikowi zale�y na czasie., 0)
	)
	else
	(
		hrp_Tip(playerid, /praca (pralnia | warsztat))
	)
	
	return 1
)