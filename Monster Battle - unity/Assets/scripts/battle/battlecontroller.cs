using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public enum FieldPosition
{
	POSITION_DEFENSIVE,
	POSITION_NEUTRAL,
	POSITION_OFFENSIVE
};

public class battlecontroller : MonoBehaviour
{
	public messageboardcontroller logNormal;
	public messageboardcontroller logRequest1;
	public messageboardcontroller logRequest2;
	public messageboardcontroller logError1;
	public messageboardcontroller logError2;

	public soundcontroller sound_controller;
	public AudioClip sfx_error;
	public AudioClip sfx_summon_monster;
	public AudioClip sfx_summon_card;
	public GameObject superEffectiveIndicator;
	public GameObject notVeryEffectiveIndicator;
	public debuginfocontroller debug_controller;
	public changescene fadeScript;
	public nfccontroller nfc;
	public moveanimatorcontroller anim_controller;
	public GameObject[] MONSTER_PREFABS;
	public GameObject[] CARD_PREFABS;
	public int TEAM_SIZE;
	private int battle_state;
	private int attack_state;

	private GameObject[] monsters1;
	private GameObject[] monsters2;
	private int current_monster1 = -1;
	private int current_monster2 = -1;
	private int current_card1 = -1;
	private int current_card2 = -1;
	private FieldPosition field_position1;
	private FieldPosition field_position2;

	private int[] cooldowns1;
	private int[] cooldowns2;

	void PushNormalMessage(string message)
	{
		logNormal.PushMessage (message, MessageStyle.NORMAL);
	}

	void PushErrorMessage(string message, int player)
	{
		if (player == 1)
			logError1.PushMessage (message, MessageStyle.ERROR);
		else
			logError2.PushMessage (message, MessageStyle.ERROR);
	}

	void PushRequestMessage(string message, int player)
	{
		if (player == 1)
			logRequest1.PushMessage (message, MessageStyle.REQUEST);
		else
			logRequest2.PushMessage (message, MessageStyle.REQUEST);
	}

	void Start ()
	{
		TEAM_SIZE = 2;

		//Impede a tela do celular de suspender
		Screen.sleepTimeout = SleepTimeout.NeverSleep;

		monsters1 = new GameObject[TEAM_SIZE];
		monsters2 = new GameObject[TEAM_SIZE];
		field_position1 = FieldPosition.POSITION_NEUTRAL;
		field_position2 = FieldPosition.POSITION_NEUTRAL;
		battle_state = 3; //estado inicial: p1 escolhe monstro
		super_effective = false;
		not_very_effective = false;

		//Inicializa os cooldowns zerados
		cooldowns1 = new int[CARD_PREFABS.Length];
		cooldowns2 = new int[CARD_PREFABS.Length];

		for (int i = 0; i < cooldowns1.Length; i++)
		{
			cooldowns1 [i] = 0;
			cooldowns2 [i] = 0;
		}
	}

	void Update ()
	{
		if (Input.GetKeyDown(KeyCode.Escape))
			fadeScript.ChangeScene("menu3");

		//Máquina de estados
		if (battle_state == 1)
			ChooseCard (1);
		else if (battle_state == 2)
			ChooseCard (2);
		else if (battle_state == 3)
			ChooseMonster (1);
		else if (battle_state == 4)
			ChooseMonster (2);
		else if (battle_state == 5)
			ChooseMonster (1);
		else if (battle_state == 6)
			ExecuteAttack (2);
		else if (battle_state == 7)
			ChooseMonster (1);
		else if (battle_state == 8)
			ChooseMonster (2);
		else if (battle_state == 9)
			ExecuteAttack (1);
		else if (battle_state == 10)
			ChooseMonster (2);
		else if (battle_state == 11)
			ExecuteAttack (1);
		else if (battle_state == 12)
			ExecuteAttack (2);
		else if (battle_state == 13)
			ChooseMonster (1);
		else if (battle_state == 14)
			ChooseMonster (2);
		else if (battle_state == 15)
			ExecuteAttack (2);
		else if (battle_state == 16)
			ExecuteAttack (1);
		else if (battle_state == 17)
			ChooseMonster (2);
		else if (battle_state == 18)
			ChooseMonster (1);

		//P1 WINS
		else if (battle_state == 19)
		{
			SetWinScreen(1);
			battle_state = 21; //estado vazio
		}

		//P2 WINS
		else if (battle_state == 20)
		{
			SetWinScreen(2);
			battle_state = 21; //estado vazio
		}
	}

	//Modela as transićões de estados
	void AdvanceState()
	{
		if (battle_state == 1)
		{
			battle_state = 2;
		}
		else if (battle_state == 2)
		{
			//As duas cartas são swap
			if (current_card1 == 0 && current_card2 == 0)
				battle_state = 3;
			//A primeira é swap a segunda é ataque
			else if (current_card1 == 0 && current_card2 != 0)
				battle_state = 5;
			//A primeira é ataque a segunda é swap
			else if (current_card1 != 0 && current_card2 == 0)
				battle_state = 8;
			//As duas são ataque e monstro1.speed >= monstro2.speed
			else if (current_card1 != 0 && current_card2 != 0 && GetCurrentMonster (1).speed >= GetCurrentMonster (2).speed) {
				battle_state = 11;
				attack_state = 1;
			}
			//As duas são ataque e monstro1.speed < monstro2.speed
			else
			{
				battle_state = 15;
				attack_state = 1;
			}
		} 
		else if (battle_state == 3) {
			battle_state = 4;
		}
		else if (battle_state == 4) {
			battle_state = 1;
		}
		else if (battle_state == 5)
		{
			battle_state = 6;
			attack_state = 1;
		}
		else if (battle_state == 6)
		{
			//CurrentMonster 1 está vivo
			if (GetCurrentMonster (1).GetCurrentHP () > 0)
				battle_state = 1;
			//Morreu
			else
				battle_state = 7;
		}
		else if (battle_state == 7)
		{
			//Se ainda tem monstros no time
			if (IsTeamAlive (1))
				battle_state = 1;
			else
				battle_state = 20;
		}
		else if (battle_state == 8)
		{
			battle_state = 9;
			attack_state = 1;
		}
		else if (battle_state == 9)
		{
			//CurrentMonster 2 está vivo
			if (GetCurrentMonster (2).GetCurrentHP () > 0)
				battle_state = 1;
			//Morreu
			else
				battle_state = 10;
		}
		else if (battle_state == 10)
		{
			//Se ainda tem monstros no time
			if (IsTeamAlive (2))
				battle_state = 1;
			else
				battle_state = 19;
		}
		else if (battle_state == 11)
		{
			//CurrentMonster 2 está vivo
			if (GetCurrentMonster (2).GetCurrentHP () > 0)
			{
				battle_state = 12;
				attack_state = 1;
			}
			//Morreu
			else
				battle_state = 14;
		}
		else if (battle_state == 12)
		{
			//CurrentMonster 1 está vivo
			if (GetCurrentMonster (1).GetCurrentHP () > 0)
				battle_state = 1;
			//Morreu
			else
				battle_state = 13;
		}
		else if (battle_state == 13)
		{
			//Se ainda tem monstros no time
			if (IsTeamAlive (1))
				battle_state = 1;
			else
				battle_state = 20;
		}
		else if (battle_state == 14) {
			//Se ainda tem monstros no time
			if (IsTeamAlive (2))
				battle_state = 1;
			else
				battle_state = 19;
		}
		else if (battle_state == 15)
		{
			//CurrentMonster 1 está vivo
			if (GetCurrentMonster (1).GetCurrentHP () > 0) 
			{
				battle_state = 16;
				attack_state = 1;
			}
			//Morreu
			else
				battle_state = 18;
		}
		else if (battle_state == 16)
		{
			//CurrentMonster 2 está vivo
			if (GetCurrentMonster (2).GetCurrentHP () > 0)
				battle_state = 1;
			//Morreu
			else
				battle_state = 17;
		}
		else if (battle_state == 17)
		{
			//Se ainda tem monstros no time
			if (IsTeamAlive (2))
				battle_state = 1;
			else
				battle_state = 19;
		}
		else if (battle_state == 18)
		{
			//Se ainda tem monstros no time
			if (IsTeamAlive (1))
				battle_state = 1;
			else
				battle_state = 20;
		}
		else if (battle_state == 19) {
			battle_state = 19; //Fica no mesmo estado
		}
		else if (battle_state == 20) {
			battle_state = 20; //Fica no mesmo estado
		}

		//Se o estado for de escolha de cartas é o inicio do turno atualiza os cooldowns
		if (battle_state == 1)
			UpdateCooldown ();
	}

	private void SetWinScreen(int player)
	{
		//Ativa o texto
		GameObject textwinner = GameObject.Find("Canvas").transform.GetChild(2).gameObject;
		textwinner.SetActive (true);

		//Seta o texto
		Text textwinner1 = textwinner.transform.GetChild(0).GetComponent<Text> ();
		Text textwinner2 = textwinner.transform.GetChild(1).GetComponent<Text> ();
		textwinner1.text = "Player " + player.ToString() + "\nwins!";
		textwinner2.text = "Player " + player.ToString() + "\nwins!";

		//Ativa os botões
		GameObject.Find("Canvas").transform.GetChild(0).gameObject.SetActive(true);
		GameObject.Find("Canvas").transform.GetChild(1).gameObject.SetActive(true);

		//Desativa os outros objetos
		GameObject.Find("UI").transform.GetChild(0).gameObject.SetActive(true);
		GameObject.Find("UI").transform.GetChild(1).gameObject.SetActive(true);
		GameObject.Find("UI").transform.GetChild(2).gameObject.SetActive(true);

		//Remove as mensagens de log
		PushNormalMessage ("");
		PushErrorMessage ("", 1);
		PushErrorMessage ("", 2);
		PushRequestMessage ("", 1);
		PushRequestMessage ("", 2);
	}

	void ChooseMonster(int player)
	{
		PushRequestMessage ("Player " + player.ToString() + " choose your monster", player);

		//Se não possui mais monstros avanca estado
		if ((player == 1 && IsTeamAlive (1) == false) || (player == 2 && IsTeamAlive (2) == false))
			AdvanceState ();

		int monster_id = -1;

		//Escolhe monstro com NFC
		monster_id = nfc.GetMonsterFromNFC();

		//Escolhe monstro com a entrada do teclado
		if (Input.GetKeyDown (KeyCode.Alpha1))
			monster_id = 1;
		else if (Input.GetKeyDown (KeyCode.Alpha2))
			monster_id = 2;
		else if (Input.GetKeyDown (KeyCode.Alpha3))
			monster_id = 3;
		else if (Input.GetKeyDown (KeyCode.Alpha4))
			monster_id = 4;
		else if (Input.GetKeyDown (KeyCode.Alpha5))
			monster_id = 5;
		else if (Input.GetKeyDown (KeyCode.Alpha6))
			monster_id = 6;
		else if (Input.GetKeyDown (KeyCode.Alpha7))
			monster_id = 7;
		else if (Input.GetKeyDown (KeyCode.Alpha8))
			monster_id = 8;

		//Escolhe monstro com keypad de debug
		if (debug_controller.gameObject.activeSelf)
		{
			int debug_id = debug_controller.GetMonsterFromKeypad ();
			if (debug_id != -1)
				monster_id = debug_id;
		}

		//Se escolheu um monstro
		if (monster_id != -1)
		{
			GameObject chosen_monster = GetMonsterFromID (monster_id);

			//Se é o monstro que já está em campo não deixa
			if (GetCurrentMonster (player) != null && chosen_monster.GetComponent<monster> ().uiname == GetCurrentMonster (player).uiname)
			{
				sound_controller.PlaySFX (sfx_error);
				PushErrorMessage ("Invalid. This monster is already\n on battlefield.", player);
			}

			//Se o Monstro existe e está no time
			else if (IsMonsterOnTeam (player, chosen_monster))
			{
				//Se o monstro está vivo
				if (IsMonsterAlive (player, chosen_monster)) 
				{
					//Seta como current
					SetCurrentMonster (player, chosen_monster);
					AdvanceState ();
					PushRequestMessage ("", player);
					PushErrorMessage ("", player);
					PushNormalMessage ("Player " + player.ToString () + " chose " + chosen_monster.GetComponent<monster> ().uiname + "!");
					sound_controller.PlaySFX (sfx_summon_monster);
				}

				//O monstro morreu, não é valido
				else
				{
					PushErrorMessage("Invalid. This monster was defeated.", player);
					sound_controller.PlaySFX (sfx_error);
				}
			}

			//O monstro não está no time mas há vaga para ele
			else if(TeamSlotsLeft(player) > 0)
			{
				InsertMonsterOnTeam (player, chosen_monster);
				SetCurrentMonster(player, chosen_monster);
				AdvanceState ();
				PushRequestMessage ("", player);
				PushErrorMessage ("", player);
				PushNormalMessage("Player " + player.ToString() + " chose " + chosen_monster.GetComponent<monster>().uiname + "!");
				sound_controller.PlaySFX (sfx_summon_monster);
			}

			//O monstro não está no time e não há vaga para ele
			else
			{
				PushErrorMessage("Invalid. Your team is full", player);
				sound_controller.PlaySFX (sfx_error);
			}
		}
	}
		
	void ChooseCard(int player)
	{
		PushRequestMessage ("Player " + player.ToString() + " choose your card", player);

		int card_id = -1;

		//Escolhe carta com NFC
		card_id = nfc.GetCardFromNFC();

		//Escolhe carta com a entrada
		if (Input.GetKeyDown (KeyCode.Alpha0))
			card_id = 0;
		else if (Input.GetKeyDown (KeyCode.Alpha1))
			card_id = 1;
		else if (Input.GetKeyDown (KeyCode.Alpha2))
			card_id = 2;
		else if (Input.GetKeyDown (KeyCode.Alpha3))
			card_id = 3;
		else if (Input.GetKeyDown (KeyCode.Alpha4))
			card_id = 4;
		else if (Input.GetKeyDown (KeyCode.Alpha5))
			card_id = 5;
		else if (Input.GetKeyDown (KeyCode.Alpha6))
			card_id = 6;
		else if (Input.GetKeyDown (KeyCode.Alpha7))
			card_id = 7;
		else if (Input.GetKeyDown (KeyCode.Alpha8))
			card_id = 8;

		//Escolhe carta com keypad de debug
		if (debug_controller.gameObject.activeSelf)
		{
			int debug_id = debug_controller.GetCardFromKeypad ();
			if (debug_id != -1)
				card_id = debug_id;
		}

		//Se escolheu uma carta
		if (card_id != -1)
		{
			//Se a carta está com cooldown zerado
			if ((player == 1 && cooldowns1 [card_id] == 0) || (player == 2 && cooldowns2 [card_id] == 0)) 
			{
				int chosen_card = GetCardFromID (card_id);

				//Se não pode usar a carta pq é de troca e só tem 1 monstro
				if (card_id == 0 && GetNumTeamAliveMonsters (player) <= 1)
				{
					PushErrorMessage ("Invalid. You have no more \nmonsters to swap.", player);
					sound_controller.PlaySFX (sfx_error);
				}

				//Se não pode usar a carta por causa do tipo
				else if (card_id != 0
					&& CARD_PREFABS [chosen_card].GetComponent<card> ().type != GameType.NATURALIS
					&& GetCurrentMonster (player).type != CARD_PREFABS [chosen_card].GetComponent<card> ().type)
				{
					PushErrorMessage ("Invalid. This monster cannot \nexecute this attack.", player);
					sound_controller.PlaySFX (sfx_error);
				} 

				//Se pode usar a carta
				else
				{
					if (player == 1)
						cooldowns1 [card_id] = CARD_PREFABS [chosen_card].GetComponent<card> ().cooldown+1;
					else
						cooldowns2 [card_id] = CARD_PREFABS [chosen_card].GetComponent<card> ().cooldown+1;

					SetCurrentCard (player, chosen_card);
					PushErrorMessage ("", player);
					PushRequestMessage ("", player);
					AdvanceState ();
					sound_controller.PlaySFX (sfx_summon_card);
				}
			}

			//Ainda falta esperar o cooldown
			else
			{
				int turns = cooldowns1 [card_id];
				if (player == 2)
					turns = cooldowns2 [card_id];

				PushErrorMessage ("Invalid. Wait " + turns + " turns\n for cooldown.", player);
			}
		}
	}

	private void UpdateCooldown()
	{
		for (int i = 0; i < cooldowns1.Length; i++)
		{
			if(cooldowns1[i] > 0)
				cooldowns1 [i]--;
			if(cooldowns2[i] > 0)
				cooldowns2 [i]--;
		}
	}
		
	public bool IsChoosingMonster(int player)
	{
		if (player == 1 && (
			battle_state == 3
		    || battle_state == 5
			|| battle_state == 7
			|| battle_state == 13
			|| battle_state == 18))
			return true;
		else if (player == 2 && (
			battle_state == 4
		    || battle_state == 8
			|| battle_state == 10
			|| battle_state == 14
		    || battle_state == 17))
			return true;
		else
			return false;
	}

	public bool IsChoosingCard(int player)
	{
		if (player == 1 && battle_state == 1)
			return true;
		else if (player == 2 && battle_state == 2)
			return true;
		else
			return false;
	}

	public bool HasChosenCard(int player)
	{
		if (player == 1 && battle_state == 2)
			return true;
		return false;
	}

	public int GetTeamSize()
	{
		return TEAM_SIZE;
	}

	public monster GetMonster(int player, int index)
	{
		if (player == 1 && monsters1 [index] != null)
			return monsters1 [index].GetComponent<monster> ();
		else if (player == 2 && monsters2 [index] != null)
			return monsters2 [index].GetComponent<monster> ();
		else
			return null;
	}

	public FieldPosition GetFieldPosition(int player)
	{
		if (player == 1)
			return field_position1;
		else
			return field_position2;
	}

	public void SetFieldPosition(int player, FieldPosition f)
	{
		if (player == 1 && (battle_state == 1 || battle_state == 2))
			field_position1 = f;
		else if(player == 2 && (battle_state == 1 || battle_state == 2))
			field_position2 = f;
	}

	public monster GetCurrentMonster(int player)
	{
		if (player == 1 && current_monster1 >= 0 && current_monster1 < TEAM_SIZE)
			return monsters1[current_monster1].GetComponent<monster>();
		else if (player == 2 && current_monster2 >= 0 && current_monster2 < TEAM_SIZE)
			return monsters2[current_monster2].GetComponent<monster>();
		return null;
	}

	public card GetCurrentCard(int player)
	{
		if (player == 1 && current_card1 >= 0)
			return CARD_PREFABS[current_card1].GetComponent<card>();
		else if (player == 2 && current_card2 >= 0)
			return CARD_PREFABS[current_card2].GetComponent<card>();
		return null;
	}

	GameObject GetMonsterFromID (int monster_id)
	{
		if (monster_id == 1)
			return MONSTER_PREFABS [0];
		else if (monster_id == 2)
			return MONSTER_PREFABS [1];
		else if (monster_id == 3)
			return MONSTER_PREFABS [2];
		else if (monster_id == 4)
			return MONSTER_PREFABS [3];
		else if (monster_id == 5)
			return MONSTER_PREFABS [4];
		else if (monster_id == 6)
			return MONSTER_PREFABS [5];
		else if (monster_id == 7)
			return MONSTER_PREFABS [6];
		else if (monster_id == 8)
			return MONSTER_PREFABS [7];
		else
			return null;
	}

	int GetCardFromID (int card_id)
	{
		if (card_id == 0)
			return 0;
		else if (card_id == 1)
			return 1;
		else if (card_id == 2)
			return 2;
		else if (card_id == 3)
			return 3;
		else if (card_id == 4)
			return 4;
		else if (card_id == 5)
			return 5;
		else if (card_id == 6)
			return 6;
		else if (card_id == 7)
			return 7;
		else if (card_id == 8)
			return 8;
		else
			return -1;
	}

	public bool IsTeamAlive(int player)
	{
		for(int i = 0; i < TEAM_SIZE; i++)
		{
			if (player == 1 && (monsters1[i] == null || monsters1 [i].GetComponent<monster> ().GetCurrentHP() > 0))
				return true;
			else if (player == 2 && (monsters2[i] == null || monsters2 [i].GetComponent<monster> ().GetCurrentHP() > 0))
				return true;
		}

		return false;
	}

	public int GetNumTeamAliveMonsters(int player)
	{
		int alive_monsters = 0;

		for(int i = 0; i < TEAM_SIZE; i++)
		{
			if (player == 1 && (monsters1 [i] == null || monsters1 [i].GetComponent<monster> ().GetCurrentHP () > 0))
				alive_monsters++;
			else if (player == 2 && (monsters2 [i] == null || monsters2 [i].GetComponent<monster> ().GetCurrentHP () > 0))
				alive_monsters++;
		}

		return alive_monsters;
	}

	bool IsMonsterOnTeam (int player, GameObject chosen_monster)
	{
		for (int i = 0; i < TEAM_SIZE; i++)
		{
			if (player == 1 && monsters1 [i] != null && monsters1 [i].GetComponent<monster> ().uiname == chosen_monster.GetComponent<monster> ().uiname)
				return true;
			else if (player == 2 && monsters2 [i] != null && monsters2 [i].GetComponent<monster> ().uiname == chosen_monster.GetComponent<monster> ().uiname)
				return true;
		}

		return false;
	}

	bool IsMonsterAlive (int player, GameObject chosen_monster)
	{
		if (chosen_monster != null)
		{
			for (int i = 0; i < TEAM_SIZE; i++)
			{
				if (player == 1
				   && monsters1 [i] != null
				   && monsters1 [i].GetComponent<monster> ().uiname == chosen_monster.GetComponent<monster> ().uiname
				   && monsters1 [i].GetComponent<monster> ().GetCurrentHP () > 0)
					return true;
				else if (player == 2
				       && monsters1 [i] != null
				       && monsters2 [i].GetComponent<monster> ().uiname == chosen_monster.GetComponent<monster> ().uiname
				       && monsters2 [i].GetComponent<monster> ().GetCurrentHP () > 0)
					return true;
			}
		}

		return false;
	}

	void SetCurrentMonster (int player, GameObject chosen_monster)
	{
		bool done = false;

		for (int i = 0; i < TEAM_SIZE && !done; i++)
		{
			if (player == 1 && monsters1 [i] != null && monsters1 [i].GetComponent<monster> ().uiname == chosen_monster.GetComponent<monster> ().uiname) {
				current_monster1 = i;
				done = true;
			} else if (player == 2 && monsters2 [i] != null && monsters2 [i].GetComponent<monster> ().uiname == chosen_monster.GetComponent<monster> ().uiname) {
				current_monster2 = i;
				done = true;
			}
		}
	}

	void SetCurrentCard(int player, int chosen_card)
	{
		if (player == 1)
			current_card1 = chosen_card;
		else
			current_card2 = chosen_card;
	}

	int TeamSlotsLeft(int player)
	{
		int cont_slots = 0;

		for (int i = 0; i < TEAM_SIZE; i++)
		{
			if (player == 1 && monsters1 [i] == null)
				cont_slots++;
			else if (player == 2 && monsters2 [i] == null)
				cont_slots++;
		}

		return cont_slots;
	}

	void InsertMonsterOnTeam (int player, GameObject chosen_monster)
	{
		bool inserted = false;

		for (int i = 0; i < TEAM_SIZE && !inserted; i++)
		{
			if (player == 1 && monsters1 [i] == null) {
				monsters1 [i] = (GameObject)Instantiate (chosen_monster);
				monsters1 [i].GetComponent<monster> ().InitializeCurrentHP ();
				inserted = true;
			} else if (player == 2 && monsters2 [i] == null) {
				monsters2 [i] = (GameObject)Instantiate (chosen_monster);
				monsters2 [i].GetComponent<monster> ().InitializeCurrentHP ();
				inserted = true;
			}
		}
	}

	void ExecuteAttack(int player)
	{
		if (attack_state == 1)
			ComputeDamage (player);
		else if (attack_state == 2)
			MissAnimation (player);
		else if (attack_state == 3)
			AttackAnimation (player);
		else if (attack_state == 4)
			SlowLifebarDecay (player);
		else
		{
			if(anim_controller.IsAnimatorReadyToPlay())
				AdvanceState ();
		}
	}

	int damage;
	void ComputeDamage(int player)
	{
		PushNormalMessage (GetCurrentMonster(player).uiname + " used " + GetCurrentCard(player).uiname + "!!!");

		FieldPosition field_position_atk;
		FieldPosition field_position_def;
		GameObject monster_atk;
		GameObject monster_def;
		int current_card_id; 
		GameObject card_atk;

		if (player == 1)
		{
			field_position_atk = field_position1;
			field_position_def = field_position2;
			monster_atk = monsters1 [current_monster1];
			monster_def = monsters2 [current_monster2];
			current_card_id = current_card1;
			card_atk = CARD_PREFABS [current_card1];
		} 
		else
		{
			field_position_atk = field_position2;
			field_position_def = field_position1;
			monster_atk = monsters2 [current_monster2];
			monster_def = monsters1 [current_monster1];
			current_card_id = current_card2;
			card_atk = CARD_PREFABS [current_card2];
		}

		float fieldPositionDamageBonus = 0.25f;
		float atk_multiplier = 1.0f;
		if (field_position_atk == FieldPosition.POSITION_DEFENSIVE)
			atk_multiplier -= fieldPositionDamageBonus;
		else if (field_position_atk == FieldPosition.POSITION_OFFENSIVE)
			atk_multiplier += fieldPositionDamageBonus;

		float def_multiplier = 1.0f;
		if (field_position_def == FieldPosition.POSITION_DEFENSIVE)
			def_multiplier += fieldPositionDamageBonus;
		else if (field_position_def == FieldPosition.POSITION_OFFENSIVE)
			def_multiplier -= fieldPositionDamageBonus;

		//Se errou o golpe
		if (UnityEngine.Random.Range (0, 99) > card_atk.GetComponent<card> ().accuracy)
		{
			//Vai para o MissAnimation
			PushNormalMessage (GetCurrentMonster(player).uiname + " missed!!!");
			anim_controller.PlayAnimation(9, player, field_position1, field_position2);
			attack_state = 2;
		}

		//Acertou o golpe
		else
		{
			float type_multiplier = gametype.TypeMultiplier(card_atk.GetComponent<card> ().type, monster_def.GetComponent<monster>().type);

			if (type_multiplier >= gametype.TYPE_ADVANTAGE_MULTIPLIER)
				super_effective = true;
			else if (type_multiplier < gametype.TYPE_NEUTRAL_MULTIPLIER)
				not_very_effective = true;

			damage = (int)((0.84f*(((float)monster_atk.GetComponent<monster>().attack*atk_multiplier)/((float)monster_def.GetComponent<monster>().defense*def_multiplier))*((float)card_atk.GetComponent<card> ().power) + 2.0f)*type_multiplier);

			//Vai para o AttackAnimation
			anim_controller.PlayAnimation(current_card_id, player, field_position1, field_position2);
			attack_state = 3;
		}
	}

	void MissAnimation(int player)
	{
		if (anim_controller.FinishedCurrentAnimation ())
		{
			anim_controller.ResetAnimator ();
			attack_state = 5;
		}
	}

	void AttackAnimation(int player)
	{
		//Vai para o SlowLifebarDecay
		if (anim_controller.FinishedCurrentAnimation ())
		{
			anim_controller.ResetAnimator ();
			time_count = 0.0f;
			damage_count = 0;
			attack_state = 4;
		}
	}

	int damage_count;
	float time_count;
	bool super_effective;
	bool not_very_effective;
	void SlowLifebarDecay(int player)
	{
		DisplaySuperEffectiveSprite (player);
		GameObject monster_def;
		float speed = 100;

		if (player == 1)
			monster_def = monsters2 [current_monster2];
		else
			monster_def = monsters1 [current_monster1];

		//Tira aos poucos
		time_count += speed * Time.deltaTime;

		if (time_count >= 1.0f)
		{
			time_count = 0.0f;
			damage_count++;
			monster_def.GetComponent<monster> ().DoDamage (1);

			//Se tirou o que queria encerra
			if (damage_count >= damage || monster_def.GetComponent<monster>().GetCurrentHP() <= 0)
			{
				if (super_effective)
				{
					PushNormalMessage ("It's super effective!!!");
					super_effective = false;
					superEffectiveIndicator.SetActive (false);
				}

				if (not_very_effective)
				{
					PushNormalMessage ("It's not very effective...");
					not_very_effective = false;
					notVeryEffectiveIndicator.SetActive (false);
				}

				PushNormalMessage ("it caused " + damage.ToString() + " damage.");
				attack_state = 5;
			}
		}
	}
		
	void DisplaySuperEffectiveSprite(int player)
	{
		if (attack_state == 4)
		{
			if (super_effective)
			{
				superEffectiveIndicator.SetActive (true);

				if (player == 2) {
					if (field_position1 == FieldPosition.POSITION_DEFENSIVE)
						superEffectiveIndicator.transform.position = new Vector3 (-5.1f, 2.0f, 0.0f);
					else if (field_position1 == FieldPosition.POSITION_NEUTRAL)
						superEffectiveIndicator.transform.position = new Vector3 (-3.0f, 2.0f, 0.0f);
					else if (field_position1 == FieldPosition.POSITION_OFFENSIVE)
						superEffectiveIndicator.transform.position = new Vector3 (-1.0f, 2.0f, 0.0f);
				} else {
					if (field_position2 == FieldPosition.POSITION_DEFENSIVE)
						superEffectiveIndicator.transform.position = new Vector3 (5.1f, 2.0f, 0.0f);
					else if (field_position2 == FieldPosition.POSITION_NEUTRAL)
						superEffectiveIndicator.transform.position = new Vector3 (3.0f, 2.0f, 0.0f);
					else if (field_position2 == FieldPosition.POSITION_OFFENSIVE)
						superEffectiveIndicator.transform.position = new Vector3 (1.0f, 2.0f, 0.0f);
				}
			}

			else if (not_very_effective)
			{
				notVeryEffectiveIndicator.SetActive (true);

				if (player == 2)
				{
					if (field_position1 == FieldPosition.POSITION_DEFENSIVE)
						notVeryEffectiveIndicator.transform.position = new Vector3 (-5.1f, 2.0f, 0.0f);
					else if (field_position1 == FieldPosition.POSITION_NEUTRAL)
						notVeryEffectiveIndicator.transform.position = new Vector3 (-3.0f, 2.0f, 0.0f);
					else if (field_position1 == FieldPosition.POSITION_OFFENSIVE)
						notVeryEffectiveIndicator.transform.position = new Vector3 (-1.0f, 2.0f, 0.0f);
				} else {
					if (field_position2 == FieldPosition.POSITION_DEFENSIVE)
						notVeryEffectiveIndicator.transform.position = new Vector3 (5.1f, 2.0f, 0.0f);
					else if (field_position2 == FieldPosition.POSITION_NEUTRAL)
						notVeryEffectiveIndicator.transform.position = new Vector3 (3.0f, 2.0f, 0.0f);
					else if (field_position2 == FieldPosition.POSITION_OFFENSIVE)
						notVeryEffectiveIndicator.transform.position = new Vector3 (1.0f, 2.0f, 0.0f);
				}
			}
		} 

		else
		{
			superEffectiveIndicator.SetActive (false);
			notVeryEffectiveIndicator.SetActive (false);
		}
	}
}
