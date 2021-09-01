using UnityEngine;
using System.Collections;

public class soundcontroller : MonoBehaviour
{
	public AudioClip BGM_clip;

	private AudioSource BGM_player;
	private AudioSource SFX_player;
	private float BGM_volume;
	private float SFX_volume;

	void Start ()
	{
		//Lê volumes do arquivo de configuracões
		BGM_volume = PlayerPrefs.GetFloat ("BGM_volume", 0.5f);
		SFX_volume = PlayerPrefs.GetFloat ("SFX_volume", 0.5f);

		//Pega referencia dos audiosources
		BGM_player = transform.GetChild(0).gameObject.GetComponent<AudioSource>();
		SFX_player = transform.GetChild(1).gameObject.GetComponent<AudioSource>();

		//Coloca música de fundo pra tocar
		BGM_player.clip = BGM_clip;
		BGM_player.volume = BGM_volume;
		BGM_player.Play ();
	}

	public void PlayBGM(AudioClip BGM_clip)
	{
		BGM_player.Stop ();
		BGM_player.clip = BGM_clip;
		BGM_player.Play ();
	}

	public void PlaySFX(AudioClip SFX_clip)
	{
		SFX_player.Stop ();
		SFX_player.clip = SFX_clip;
		SFX_player.Play ();
	}

	public void SetBGMVolume(float volume)
	{
		BGM_volume = volume;
		BGM_player.volume = BGM_volume;
	}

	public void SetSFXVolume(float volume)
	{
		SFX_volume = volume;
		SFX_player.volume = SFX_volume;
	}

	public void SaveVolumeConfiguration()
	{
		PlayerPrefs.SetFloat ("BGM_volume", BGM_volume);
		PlayerPrefs.SetFloat ("SFX_volume", SFX_volume);
	}

	public bool IsPlayingSFX()
	{
		return SFX_player.isPlaying;
	}
}
