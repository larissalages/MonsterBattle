using UnityEngine;
using System.Collections; 

public class monster : MonoBehaviour
{
	public Sprite image;
	public Sprite portrait;
	public string uiname;
	public string description;

	public GameType type;
	public int hp;
	public int attack;
	public int defense;
	public int speed;

	int current_hp;

	public void InitializeCurrentHP()
	{
		current_hp = hp;
	}

	public int GetCurrentHP()
	{
		return current_hp;
	}

	public float GetHPProportion()
	{
		return ((float)current_hp)/((float)hp);
	}

	public void SetCurrentHP(int current_hp)
	{
		this.current_hp = current_hp;
	}

	public void DoDamage(int damage)
	{
		current_hp -= damage;

		if (current_hp < 0)
			current_hp = 0;
	}

	public static int GetMonsterIDFromTag(string tag)
	{
		int monster_id = -1;

		if (tag == "04AE9C5ABB2B80") //GORUGA
			monster_id = 1;
		else if (tag == "04DF9D5ABB2B80") //CLUMSY DRAGON
			monster_id = 2;
		else if (tag == "04C59D5ABB2B80") //NALOTH
			monster_id = 3;
		else if (tag == "04C89C5ABB2B80") //ECHO
			monster_id = 4;
		else if (tag == "04E09C5ABB2B80") //DRAMELEON
			monster_id = 5;
		else if (tag == "04FA9C5ABB2B80") //RHAEGON
			monster_id = 6;
		else if (tag == "F12AF252") //LILYFOX
			monster_id = 7;
		else if (tag == "04F79D5ABB2B80") //CARITH
			monster_id = 8;

		return monster_id;
	}
}
