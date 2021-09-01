using UnityEngine;
using System.Collections;

public class highlightcontroller : MonoBehaviour
{
	public battlecontroller battle_script;

	public GameObject highlight_region_def1;
	public GameObject highlight_region_neu1;
	public GameObject highlight_region_atk1;
	public GameObject highlight_region_def2;
	public GameObject highlight_region_neu2;
	public GameObject highlight_region_atk2;
	public GameObject highlight_choose_monster1;
	public GameObject highlight_choose_monster2;

	private float speed;
	private float min_alpha;
	private float max_alpha;
	private float alpha;
	private int direction;
	private float hi_choose_r;
	private float hi_choose_g;
	private float hi_choose_b;

	private float hi_chosen_r;
	private float hi_chosen_g;
	private float hi_chosen_b;

	void Start()
	{
		speed = 1.8f;
		min_alpha = 0.3f;
		max_alpha = 1.0f;
		alpha = max_alpha;
		direction = -1;

		//Cor quando escolhendo carta
		hi_choose_r = 255.0f/255.0f;
		hi_choose_g = 80.0f/255.0f;
		hi_choose_b = 0.0f/255.0f;

		//Cor quando escolhida a carta
		hi_chosen_r = 255.0f/255.0f;
		hi_chosen_g = 255.0f/255.0f;
		hi_chosen_b = 255.0f/255.0f;
	}

	private void UpdateAlpha()
	{
		if (direction == 1)
		{
			alpha += speed * Time.deltaTime;

			if (alpha > max_alpha)
			{
				alpha = max_alpha;
				direction = -1;
			}
		}

		else if (direction == -1)
		{
			alpha -= speed * Time.deltaTime;

			if (alpha < min_alpha)
			{
				alpha = min_alpha;
				direction = 1;
			}
		}
	}

	private Color GetColor(int r, int g, int b, int a)
	{
		return new Color (r/255.0f, g/255.0f, b/255.0f, a/255.0f);
	}

	private Color GetColor(int r, int g, int b, float a)
	{
		return new Color (r/255.0f, g/255.0f, b/255.0f, a);
	}

	private Color GetColor(float r, float g, float b, float a)
	{
		return new Color (r, g, b, a);
	}

	void Update () 
	{
		UpdateAlpha ();
		FieldPosition f1 = battle_script.GetFieldPosition (1);
		FieldPosition f2 = battle_script.GetFieldPosition (2);

		//Desabilita os highlights de escolha de FIELDPOSITION
		highlight_region_def1.SetActive (false);
		highlight_region_neu1.SetActive (false);
		highlight_region_atk1.SetActive (false);
		highlight_region_def2.SetActive (false);
		highlight_region_neu2.SetActive (false);
		highlight_region_atk2.SetActive (false);

		//Ativa/desativa os highlights de escolha de monstro
		if (battle_script.IsChoosingMonster (1))
			highlight_choose_monster1.SetActive (true);
		else
			highlight_choose_monster1.SetActive (false);
		
		if (battle_script.IsChoosingMonster (2))
			highlight_choose_monster2.SetActive (true);
		else
			highlight_choose_monster2.SetActive (false);

		//Ativa a cor de selecao de cartas
		if (battle_script.IsChoosingCard (1)) {
			if (f1 == FieldPosition.POSITION_DEFENSIVE)
				highlight_region_def1.GetComponent<SpriteRenderer> ().color = GetColor (hi_choose_r, hi_choose_g, hi_choose_b, alpha);
			else if (f1 == FieldPosition.POSITION_NEUTRAL)
				highlight_region_neu1.GetComponent<SpriteRenderer> ().color = GetColor (hi_choose_r, hi_choose_g, hi_choose_b, alpha);
			else if (f1 == FieldPosition.POSITION_OFFENSIVE)
				highlight_region_atk1.GetComponent<SpriteRenderer> ().color = GetColor (hi_choose_r, hi_choose_g, hi_choose_b, alpha);
		} 
		else if (battle_script.HasChosenCard (1))
		{
			if (f1 == FieldPosition.POSITION_DEFENSIVE)
				highlight_region_def1.GetComponent<SpriteRenderer> ().color = GetColor(hi_chosen_r, hi_chosen_g, hi_chosen_b, 1.0f);
			else if (f1 == FieldPosition.POSITION_NEUTRAL)
				highlight_region_neu1.GetComponent<SpriteRenderer> ().color = GetColor(hi_chosen_r, hi_chosen_g, hi_chosen_b, 1.0f);
			else if (f1 == FieldPosition.POSITION_OFFENSIVE)
				highlight_region_atk1.GetComponent<SpriteRenderer> ().color = GetColor(hi_chosen_r, hi_chosen_g, hi_chosen_b, 1.0f);
		}
		else
		{
			if (f1 == FieldPosition.POSITION_DEFENSIVE)
				highlight_region_def1.GetComponent<SpriteRenderer> ().color = GetColor(255, 255, 255, 255);
			else if (f1 == FieldPosition.POSITION_NEUTRAL)
				highlight_region_neu1.GetComponent<SpriteRenderer> ().color = GetColor(255, 255, 255, 255);
			else if (f1 == FieldPosition.POSITION_OFFENSIVE)
				highlight_region_atk1.GetComponent<SpriteRenderer> ().color = GetColor(255, 255, 255, 255);
		}

		if (battle_script.IsChoosingCard (2))
		{
			if (f2 == FieldPosition.POSITION_DEFENSIVE)
				highlight_region_def2.GetComponent<SpriteRenderer> ().color = GetColor(hi_choose_r, hi_choose_g, hi_choose_b, alpha);
			else if (f2 == FieldPosition.POSITION_NEUTRAL)
				highlight_region_neu2.GetComponent<SpriteRenderer> ().color = GetColor(hi_choose_r, hi_choose_g, hi_choose_b, alpha);
			else if (f2 == FieldPosition.POSITION_OFFENSIVE)
				highlight_region_atk2.GetComponent<SpriteRenderer> ().color = GetColor(hi_choose_r, hi_choose_g, hi_choose_b, alpha);
		}
		else if (battle_script.HasChosenCard (2))
		{
			if (f2 == FieldPosition.POSITION_DEFENSIVE)
				highlight_region_def2.GetComponent<SpriteRenderer> ().color = GetColor(hi_chosen_r, hi_chosen_g, hi_chosen_b, 1.0f);
			else if (f2 == FieldPosition.POSITION_NEUTRAL)
				highlight_region_neu2.GetComponent<SpriteRenderer> ().color = GetColor(hi_chosen_r, hi_chosen_g, hi_chosen_b, 1.0f);
			else if (f2 == FieldPosition.POSITION_OFFENSIVE)
				highlight_region_atk2.GetComponent<SpriteRenderer> ().color = GetColor(hi_chosen_r, hi_chosen_g, hi_chosen_b, 1.0f);
		}
		else
		{
			if (f2 == FieldPosition.POSITION_DEFENSIVE)
				highlight_region_def2.GetComponent<SpriteRenderer> ().color = GetColor(255, 255, 255, 255);
			else if (f2 == FieldPosition.POSITION_NEUTRAL)
				highlight_region_neu2.GetComponent<SpriteRenderer> ().color = GetColor(255, 255, 255, 255);
			else if (f2 == FieldPosition.POSITION_OFFENSIVE)
				highlight_region_atk2.GetComponent<SpriteRenderer> ().color = GetColor(255, 255, 255, 255);
		}

		//Highlights dos FIELD_POSITIONS
		if(!battle_script.IsChoosingMonster (1) && battle_script.GetCurrentMonster(1) != null)
		{
			if (f1 == FieldPosition.POSITION_DEFENSIVE)
				highlight_region_def1.SetActive (true);
			else if (f1 == FieldPosition.POSITION_NEUTRAL)
				highlight_region_neu1.SetActive (true);
			else if (f1 == FieldPosition.POSITION_OFFENSIVE)
				highlight_region_atk1.SetActive (true);
		}
			
		if(!battle_script.IsChoosingMonster (2) && battle_script.GetCurrentMonster(2) != null)
		{
			if (f2 == FieldPosition.POSITION_DEFENSIVE)
				highlight_region_def2.SetActive (true);
			else if (f2 == FieldPosition.POSITION_NEUTRAL)
				highlight_region_neu2.SetActive (true);
			else if (f2 == FieldPosition.POSITION_OFFENSIVE)
				highlight_region_atk2.SetActive (true);
		}
	}
}
