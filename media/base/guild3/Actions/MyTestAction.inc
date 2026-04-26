"PaintYourHome" = G3ActionTemplate	// internal name of the action
{
GUIPresent = true;	// the action is displayed in the action bar
UICategory = "Family";	// category of the action in the action bar
OrderIndex = 25;	// the position of the action in the action bar category ActionClassName = "SimpleExecutionAction";	// the class of the action

GUIData = array
{
ActionGUIData	// begin of the filter for the actor
{
IsCharacter = 1;	// actor must be a character
IsFamilyMember = 1;	// actor must be a member of a family/dynasty
BelongsToOwnFamily = 1;	// actor must belong to the player family
IsAdult = 1;	// actor must be an adult
}
};
UsableBy = array{ "$gui.item.UsableByAdultFamilyMembers" };	// usable by information shown in the tooltip

ActionActor = "Character";	// the actor must be a character
TargetActor = "Building";	// the target must be a building

SourceScoreFormula = "1.5 + Source.Intelligence";	// the formula for the actor TargetScoreFormula = "Target.BuildingSecurity";	// the formula for the target

IconName = "PaintingTheHome";	// the icon for the action; if left out the game will use an icon with the internal action name ActionName = "PaintYourHome";	// must be identical to the internal name
DisplayName = "$PaintYourHome";	// display name of the action
Description = "$PaintYourHomeDesc";	// description of the action
Instruction = "$selectionPrompt.SelectResidence";	// instruction shown when player clicks the action

Duration = 0.0083;	// duration, 1.0 = 24 hours
Cooldown = 0.05;	// cooldown, 1.0 = 24 hours
BaseRewardXP = 25;	// XP reward if action is successful
CanFail = true;	// action can fail, so SourceScoreFormula and TargetScoreFormula are used
CriticalFactor = 0.9;	// percentage chance of a critical success or critical failure (1 - CriticalFactor) ShowSelectionPrompt = "UseTargetProfile";		// show list of possible targets

SelectionPromptCallToAction = "$selectionPrompt.SelectResidence";	// text for list of possible targets SelectionPromptNoTargetMessage = "$selectionPrompt.NoResidence";	// text when there is no valid target HideSelectionPromptCancelButton = true;	// hide cancel button

TargetTags = array{"HasBeenPainted"};	// array of tags to check in the DesiredProfiles
DesiredProfiles = array	// begin of the filter for the target
{
TargetProfileBuilding	// first target profile for a building
{
MatchTargetTags = -3;	// none of the specified Tags must be active on the target building
IncludedTypes = array{"CountryHouse", "PoorHouse", "CityHouse", "Mansion"};	// the building must be CountryHouse, PoorHouse, CityHouse or Mansion CloseToActor = 2;	// target should be close to the actor (relevant if actor is AI)
Burning = -3;	// target must not burn
FamilyProfile = TargetProfileFamily	// profile of the building owner
{
MyFamily = 3;	// family of the actor
};

// Make sure the AutoSelect profile comes first, so it will be checked first!
IsCurrentBuilding = 3;	// if the character is inside a building that matches, then…
AutoSelect = true;	// … auto select this building
},

TargetProfileBuilding	// second target profile for a building
{
MatchTargetTags = -3;	// none of the specified Tags must be active on the target building
IncludedTypes = array{"CountryHouse", "PoorHouse", "CityHouse", "Mansion"};	// the building must be CountryHouse, PoorHouse, CityHouse or Mansion CloseToActor = 2;	// target should be close to the actor (relevant if actor is AI)
Burning = -3;	// target must not burn
FamilyProfile = TargetProfileFamily	// profile of the building owner
{

MyFamily = 3;	// family of the actor
};
};
};

TargetSnapPoint = TargetSnapPoint	// aim for a snap point at the target building where the actor performs the action
{
Required = true;	// the snap point is required
ShouldReserve = true;	// the snap point should be reserved
ShouldOccupy = true;	// the snap point will be occupied

Profiles = array	// filter for the snap point
{
TargetProfileSnapPoint{ Context = "Artefact"; },	// context of the snap point
};
Animations = array	// the animation the actor should play on the snap point
{
TargetSnapPointAnimation{ Animation = "ManipulateMiddle"; },	// name of the animation
};
};

EnterBuilding = "TryEnter";	// source should try to enter a building - note stepping on the outside area of a building means entering

CriticalSuccessResult = array	// result if CRITICAL SUCCESS
{
DisplayEffect	// adds a state information in the character or building panel bottom left
{
ApplyTo = "Target";	// applied to the target
Tags = array{"HasBeenPainted"};	// adds a Tag to the target and combines the Tag with the DisplayEffect (important when the Tag is removed) DisplayGroup = "buffed";	// the display group of the effect
DisplayName = "$BuildingPaintedBuff";	// the name of the effect

Duration = 1800.0;	// IMPORTANT: this duration uses “ticks” (specified in GameplayDefault.oc with NormalYearTime
},
ModifierEffect	// adds a modifier effect to the target
{
ApplyTo = "Target";	// applied to the target
Tags = array{"HasBeenPainted"};	// adds a Tag to the target and combines the Tag with the ModifierEffect (important when the Tag is removed) ActorValue = "Health";	// affects the ActorValue “Health” of the target
Mod = 50.0;	// the ActorValue is modified by 50
Duration = 1800;	// IMPORTANT: this duration uses “ticks” (specified in GameplayDefault.oc with NormalYearTime
Recover = true;	// the modification of the actor value is removed when the duration is up
},
FunctionTriggerAction	// triggers an action
{
ApplyTo = "Source";	// applied to the source
Actions = array{"Exit"};	// array of names of (randomly) the triggered actions (Exit let the character leave the current building)
},
FunctionTrackObjectiveProgress
{
ObjectiveTypename = "IncreaseSecurity";	// changes/satisfies the desire “IncreaseSecurity” of an AI dynasty Amount = 15;	// by 15 points
},
};

SuccessResult = array	// result if SUCCESS
{
DisplayEffect	// adds a state information in the character or building panel bottom left
{
ApplyTo = "Target";	// applied to the target
Tags = array{"HasBeenPainted"};	// adds a Tag to the target and combines the Tag with the DisplayEffect (important when the Tag is removed) DisplayGroup = "buffed";	// the display group of the effect
DisplayName = "$BuildingPaintedBuff";	// the name of the effect

Duration = 1200.0;	// IMPORTANT: this duration uses “ticks” (specified in GameplayDefault.oc with NormalYearTime
},
ModifierEffect	// adds a modifier effect to the target
{
ApplyTo = "Target";	// applied to the target
Tags = array{"HasBeenPainted"};	// adds a Tag to the target and combines the Tag with the ModifierEffect (important when the Tag is removed) ActorValue = "Health";	// affects the ActorValue “Health” of the target
Mod = 25.0;	// the ActorValue is modified by 25
Duration = 1200;	// IMPORTANT: this duration uses “ticks” (specified in GameplayDefault.oc with NormalYearTime
Recover = true;	// the modification of the actor value is removed when the duration is up
},
FunctionTriggerAction	// triggers an action
{
ApplyTo = "Source";	// applied to the source
Actions = array{"Exit"};	// array of names of (randomly) the triggered actions (Exit let the character leave the current building)
},
FunctionTrackObjectiveProgress
{
ObjectiveTypename = "IncreaseSecurity";	// changes/satisfies the desire “IncreaseSecurity” of an AI dynasty Amount = 10;	// by 10 points
},
};

FailureResult = array	// result if FAILURE
{
DisplayEffect	// adds a state information in the character or building panel bottom left
{
ApplyTo = "Target";	// applied to the target
Tags = array{"HasBeenPainted"};	// adds a Tag to the target and combines the Tag with the DisplayEffect (important when the Tag is removed) DisplayGroup = "buffed";	// the display group of the effect
DisplayName = "$BuildingPaintedDebuff";	// the name of the effect

Duration = 1200.0;	// IMPORTANT: this duration uses “ticks” (specified in GameplayDefault.oc with NormalYearTime
},
ModifierEffect	// adds a modifier effect to the target
{
ApplyTo = "Target";	// applied to the target
Tags = array{"HasBeenPainted"};	// adds a Tag to the target and combines the Tag with the ModifierEffect (important when the Tag is removed) ActorValue = "Health";	// affects the ActorValue “Health” of the target
Mod = -10.0;	// the ActorValue is modified by -10
Duration = 1200;	// IMPORTANT: this duration uses “ticks” (specified in GameplayDefault.oc with NormalYearTime
Recover = true;	// the modification of the actor value is removed when the duration is up
},
FunctionTriggerAction	// triggers an action
{
ApplyTo = "Source";	// applied to the source
Actions = array{"Exit"};	// array of names of (randomly) the triggered actions (Exit let the character leave the current building)
},
};

CriticalFailureResult = array	// result if CRITICAL FAILURE
{
DisplayEffect	// adds a state information in the character or building panel bottom left
{
ApplyTo = "Target";	// applied to the target
Tags = array{"HasBeenPainted"};	// adds a Tag to the target and combines the Tag with the DisplayEffect (important when the Tag is removed) DisplayGroup = "buffed";	// the display group of the effect
DisplayName = "$BuildingPaintedDebuff";	// the name of the effect
Duration = 1800.0;	// IMPORTANT: this duration uses “ticks” (specified in GameplayDefault.oc with NormalYearTime
},
ModifierEffect	// adds a modifier effect to the target
{
ApplyTo = "Target";	// applied to the target

Tags = array{"HasBeenPainted"};	// adds a Tag to the target and combines the Tag with the ModifierEffect (important when the Tag is removed) ActorValue = "Health";	// affects the ActorValue “Health” of the target
Mod = -30.0;	// the ActorValue is modified by -30
Duration = 1800;	// IMPORTANT: this duration uses “ticks” (specified in GameplayDefault.oc with NormalYearTime
Recover = true;	// the modification of the actor value is removed when the duration is up
},
FunctionTriggerAction	// triggers an action
{
ApplyTo = "Source";	// applied to the source
Actions = array{"Exit"};	// array of names of (randomly) the triggered actions (Exit let the character leave the current building)
},
};
};