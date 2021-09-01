using UnityEngine;
using System.Collections;

public class moveanimatorcontroller : MonoBehaviour
{
	public Animator move_animator;
	public SpriteRenderer sprite_renderer;
	public soundcontroller sound_controller;

	public AudioClip[] sfx_moves;

	void Start ()
	{
		move_animator.SetInteger ("move_id", -1);
		move_animator.SetBool ("leave_posanim", false);
	}

	public void ResetAnimator()
	{
		move_animator.SetInteger ("move_id", -1);
		move_animator.SetBool ("leave_posanim", true);
	}

	public bool IsAnimatorReadyToPlay()
	{
		return move_animator.GetCurrentAnimatorStateInfo (0).IsName ("preanim");
	}

	public bool FinishedCurrentAnimation()
	{
		if (move_animator.GetCurrentAnimatorStateInfo (0).IsName ("posanim") && !sound_controller.IsPlayingSFX())
			return true;
		return false;
	}

	private void SetFlip(int player)
	{
		if (player == 2)
			sprite_renderer.flipX = true;
	}

	public void PlayAnimation(int move_id, int player, FieldPosition fieldPosition1, FieldPosition fieldPosition2)
	{
		sound_controller.PlaySFX (sfx_moves [move_id]);
		sprite_renderer.flipX = false;

		// SWAP
		if (move_id == 0) 
		{ 
			transform.localScale = new Vector3 (1f, 1f, 1f);
			transform.position = new Vector3 (0.0f, 0.0f, 0.0f);
		} 

		// AFTERSHOCK
		else if (move_id == 1) 
		{ 
			SetFlip (player);
			transform.localScale = new Vector3 (1f, 1f, 1f);

			if (player == 1)
				transform.position = new Vector3 (4.3f, 0.0f, 0.0f);
			else
				transform.position = new Vector3 (-4.3f, 0.0f, 0.0f);
		} 

		// SEISMIC BREAK
		else if (move_id == 2)
		{
			transform.localScale = new Vector3 (1.4f, 1.4f, 1.0f);

			if (player == 1)
			{
				if(fieldPosition1 == FieldPosition.POSITION_DEFENSIVE)
					transform.position = new Vector3 (6.3f, 0.0f, 0.0f);
				else if(fieldPosition1 == FieldPosition.POSITION_NEUTRAL)
					transform.position = new Vector3 (4.3f, -0.4f, 0.0f);
				else if(fieldPosition1 == FieldPosition.POSITION_OFFENSIVE)
					transform.position = new Vector3 (2.3f, 0.0f, 0.0f);
			} 

			else
			{
				if(fieldPosition2 == FieldPosition.POSITION_DEFENSIVE)
					transform.position = new Vector3 (-6.3f, 0.0f, 0.0f);
				else if(fieldPosition2 == FieldPosition.POSITION_NEUTRAL)
					transform.position = new Vector3 (-4.3f, -0.4f, 0.0f);
				else if(fieldPosition2 == FieldPosition.POSITION_OFFENSIVE)
					transform.position = new Vector3 (-2.3f, 0.0f, 0.0f);
			}
		}

		// INUNDATION
		else if (move_id == 3)
		{
			SetFlip (player);
			transform.localScale = new Vector3 (1.3f, 1.3f, 1f);

			if (player == 1)
				transform.position = new Vector3 (4.7f, 0.0f, 0.0f);
			else
				transform.position = new Vector3 (-4.7f, 0.0f, 0.0f);
		}

		// TIDAL WAVE
		else if (move_id == 4)
		{
			SetFlip (player);
			transform.localScale = new Vector3 (1.6f, 1.6f, 1f);

			if (player == 1)
				transform.position = new Vector3 (4.3f, 0.0f, 0.0f);
			else
				transform.position = new Vector3 (-4.3f, 0.0f, 0.0f);
		}

		// SKY DIVING
		else if (move_id == 5)
		{
			SetFlip (player);
			transform.localScale = new Vector3 (1.4f, 1.4f, 1f);

			if (player == 1)
			{
				if(fieldPosition1 == FieldPosition.POSITION_DEFENSIVE)
					transform.position = new Vector3 (6.3f, 0.0f, 0.0f);
				else if(fieldPosition1 == FieldPosition.POSITION_NEUTRAL)
					transform.position = new Vector3 (4.3f, 0.0f, 0.0f);
				else if(fieldPosition1 == FieldPosition.POSITION_OFFENSIVE)
					transform.position = new Vector3 (2.3f, 0.0f, 0.0f);
			} 

			else
			{
				if(fieldPosition2 == FieldPosition.POSITION_DEFENSIVE)
					transform.position = new Vector3 (-6.3f, 0.0f, 0.0f);
				else if(fieldPosition2 == FieldPosition.POSITION_NEUTRAL)
					transform.position = new Vector3 (-4.3f, 0.0f, 0.0f);
				else if(fieldPosition2 == FieldPosition.POSITION_OFFENSIVE)
					transform.position = new Vector3 (-2.3f, 0.0f, 0.0f);
			}
		}

		// TYPHOON
		else if (move_id == 6)
		{
			transform.localScale = new Vector3 (6f, 6f, 1f);

			if (player == 1)
			{
				if(fieldPosition1 == FieldPosition.POSITION_DEFENSIVE)
					transform.position = new Vector3 (6.3f, 1.0f, 0.0f);
				else if(fieldPosition1 == FieldPosition.POSITION_NEUTRAL)
					transform.position = new Vector3 (4.3f, 1.0f, 0.0f);
				else if(fieldPosition1 == FieldPosition.POSITION_OFFENSIVE)
					transform.position = new Vector3 (2.3f, 1.0f, 0.0f);
			} 

			else
			{
				if(fieldPosition2 == FieldPosition.POSITION_DEFENSIVE)
					transform.position = new Vector3 (-6.3f, 1.0f, 0.0f);
				else if(fieldPosition2 == FieldPosition.POSITION_NEUTRAL)
					transform.position = new Vector3 (-4.3f, 1.0f, 0.0f);
				else if(fieldPosition2 == FieldPosition.POSITION_OFFENSIVE)
					transform.position = new Vector3 (-2.3f, 1.0f, 0.0f);
			}
		}

		// NATURE FORCE
		else if (move_id == 7)
		{
			SetFlip (player);
			transform.localScale = new Vector3 (1.4f, 1.6f, 1f);

			if (player == 1)
			{
				if(fieldPosition1 == FieldPosition.POSITION_DEFENSIVE)
					transform.position = new Vector3 (1.3f, 0.0f, 0.0f);
				else if(fieldPosition1 == FieldPosition.POSITION_NEUTRAL)
					transform.position = new Vector3 (3.8f, 0.0f, 0.0f);
				else if(fieldPosition1 == FieldPosition.POSITION_OFFENSIVE)
					transform.position = new Vector3 (5.8f, 0.0f, 0.0f);
			} 

			else
			{
				if(fieldPosition2 == FieldPosition.POSITION_DEFENSIVE)
					transform.position = new Vector3 (-1.3f, 0.0f, 0.0f);
				else if(fieldPosition2 == FieldPosition.POSITION_NEUTRAL)
					transform.position = new Vector3 (-3.8f, 0.0f, 0.0f);
				else if(fieldPosition2 == FieldPosition.POSITION_OFFENSIVE)
					transform.position = new Vector3 (-5.8f, 0.0f, 0.0f);
			}
		}

		// STORM OF SPIRITS
		else if (move_id == 8)
		{
			SetFlip (player);
			transform.localScale = new Vector3 (1.4f, 1.8f, 1f);
			transform.position = new Vector3 (0f, 0f, 0f);
		}

		// MISS
		else if (move_id == 9)
		{
			transform.localScale = new Vector3 (0.8f, 0.8f, 1f);

			if (player == 1)
			{
				if(fieldPosition1 == FieldPosition.POSITION_DEFENSIVE)
					transform.position = new Vector3 (7.1f, -2.5f, 0.0f);
				else if(fieldPosition1 == FieldPosition.POSITION_NEUTRAL)
					transform.position = new Vector3 (4.7f, -2.5f, 0.0f);
				else if(fieldPosition1 == FieldPosition.POSITION_OFFENSIVE)
					transform.position = new Vector3 (2.3f, -2.5f, 0.0f);
			} 

			else
			{
				if(fieldPosition2 == FieldPosition.POSITION_DEFENSIVE)
					transform.position = new Vector3 (-7.1f, -2.5f, 0.0f);
				else if(fieldPosition2 == FieldPosition.POSITION_NEUTRAL)
					transform.position = new Vector3 (-4.7f, -2.5f, 0.0f);
				else if(fieldPosition2 == FieldPosition.POSITION_OFFENSIVE)
					transform.position = new Vector3 (-2.3f, -2.5f, 0.0f);
			}
		}

		//Seta variaveis da maquina de estados do animator
		move_animator.SetBool ("leave_posanim", false);

		//Inicia a animacão
		move_animator.SetInteger ("move_id", move_id);
	}
}
