using System.Collections;

public enum GameType { TERRAE, OCEANUS, CAELUM, NATURALIS };

public class gametype
{
	public static float TYPE_ADVANTAGE_MULTIPLIER = 1.40f;
	public static float TYPE_DISADVANTAGE_MULTIPLIER = 0.60f;
	public static float TYPE_NEUTRAL_MULTIPLIER = 1.0f;

	public static float TypeMultiplier(GameType type_atk, GameType type_def)
	{
		//TERRAE
		if (type_atk == GameType.TERRAE)
		{
			if (type_def == GameType.OCEANUS)
				return TYPE_DISADVANTAGE_MULTIPLIER;
			else if (type_def == GameType.CAELUM)
				return TYPE_ADVANTAGE_MULTIPLIER;
			else
				return TYPE_NEUTRAL_MULTIPLIER;
		}

		//OCEANUS
		else if (type_atk == GameType.OCEANUS)
		{
			if (type_def == GameType.CAELUM)
				return TYPE_DISADVANTAGE_MULTIPLIER;
			else if (type_def == GameType.TERRAE)
				return TYPE_ADVANTAGE_MULTIPLIER;
			else
				return TYPE_NEUTRAL_MULTIPLIER;
		}

		//CAELUM
		else if (type_atk == GameType.CAELUM)
		{
			if (type_def == GameType.TERRAE)
				return TYPE_DISADVANTAGE_MULTIPLIER;
			else if (type_def == GameType.OCEANUS)
				return TYPE_ADVANTAGE_MULTIPLIER;
			else
				return TYPE_NEUTRAL_MULTIPLIER;
		}

		//NATURALIS
		else
			return TYPE_NEUTRAL_MULTIPLIER;
	}

	public static string GetString(GameType gameType)
	{
		if(gameType == GameType.TERRAE)
			return "Terrae";
		else if(gameType == GameType.OCEANUS)
			return "Oceanus";
		else if(gameType == GameType.CAELUM)
			return "Caelum";
		else
			return "Naturalis";
	}
}
