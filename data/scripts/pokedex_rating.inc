PokedexRating_EventScript_RateInPerson:: @ 81A737B
	goto_if_questlog EventScript_ReleaseEnd
	special QuestLog_CutRecording
	call_if_set FLAG_OAK_SAW_DEX_COMPLETION, PokedexRating_EventScript_DexCompleteIntro
	call_if_unset FLAG_OAK_SAW_DEX_COMPLETION, PokedexRating_EventScript_NormalIntro
	call PokedexRating_EventScript_Rate
	return

PokedexRating_EventScript_DexCompleteIntro:: @ 81A73A4
	msgbox PokedexRating_Text_LoveSeeingYourPokedex
	return

PokedexRating_EventScript_NormalIntro:: @ 81A73AD
	msgbox PokedexRating_Text_HowIsPokedexComingAlong
	return

PokedexRating_EventScript_ShowRatingMsg:: @ 81A73B6
	copyvar VAR_0x8004, VAR_0x8009
	special GetProfOaksRatingMessage
	waitmessage
	compare VAR_RESULT, FALSE
	call_if_eq PokedexRating_EventScript_NormalFanfare
	compare VAR_RESULT, TRUE
	call_if_eq PokedexRating_EventScript_DexCompleteFanfare
	waitfanfare
	waitbuttonpress
	return

PokedexRating_EventScript_NormalFanfare:: @ 81A73D8
	playfanfare MUS_DEX_RATING
	return

PokedexRating_EventScript_DexCompleteFanfare:: @ 81A73DC
	playfanfare MUS_EVOLVED
	return

PokedexRating_EventScript_Rate:: @ 81A73E0
	setvar VAR_0x8004, HELPCONTEXT_PC_MISC
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetPokedexCount
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	copyvar VAR_0x800A, VAR_RESULT
	getnumberstring 0, VAR_0x8008 @ Num Kanto Seen
	getnumberstring 1, VAR_0x8009 @ Num Kanto Caught
	msgbox PokedexRating_Text_SeenXOwnedY
	call_if_unset FLAG_OAKS_RATING_IS_VIA_PC, PokedexRating_EventScript_SetTextColor
	call PokedexRating_EventScript_ShowRatingMsg
	compare VAR_0x800A, FALSE
	goto_if_eq PokedexRating_EventScript_EndRating  @ National Dex not enabled
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, GetPokedexCount
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	getnumberstring 0, VAR_0x8008 @ Num National Seen
	getnumberstring 1, VAR_0x8009 @ Num National Caught
	msgbox PokedexRating_Text_NationalDexSeenXOwnedY
	specialvar VAR_RESULT, HasAllMons
	compare VAR_RESULT, FALSE
	goto_if_eq PokedexRating_EventScript_DexIncomplete
	compare VAR_RESULT, TRUE
	goto_if_eq PokedexRating_EventScript_DexComplete
	end

PokedexRating_EventScript_SetTextColor:: @ 81A746D
	textcolor 0
	return

PokedexRating_EventScript_DexIncomplete:: @ 81A7470
	msgbox PokedexRating_Text_LookForwardToFilledNationalDex
	goto PokedexRating_EventScript_EndRating
	end

PokedexRating_EventScript_DexComplete:: @ 81A747E
	setflag FLAG_OAK_SAW_DEX_COMPLETION
	msgbox PokedexRating_Text_YouveCompletedDex
	goto PokedexRating_EventScript_EndRating
	end

PokedexRating_EventScript_EndRating:: @ 81A748F
	return
