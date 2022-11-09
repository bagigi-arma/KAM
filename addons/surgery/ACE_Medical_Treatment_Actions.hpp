class ACE_Medical_Treatment_Actions {
    class BasicBandage;
    class FieldDressing;
    class ApplyTourniquet;
    class RemoveTourniquet;
    class Morphine;
    class CheckPulse;
    class CPR;
    class Carbonate;
    class Defibrillator_AED_X_vehicle;

    class CheckFracture: CheckPulse {
        displayName = CSTRING(fracture_check);
        displayNameProgress = CSTRING(fracture_checking);
        category = "examine";
        treatmentLocations = 0;
        allowedSelections[] = {"LeftArm", "RightArm", "LeftLeg", "RightLeg"};
        allowSelfTreatment = QGVAR(enable_selfCheckFracture);
        medicRequired = QGVAR(fractureCheck_MedLevel);
        treatmentTime = QGVAR(fractureCheck_Time);
        items[] = {};
        condition = QUOTE(([ARR_4(_medic, _patient, _bodyPart, 5)] call FUNC(fractureCheck)) && (GVAR(enable_fracture)));
        callbackSuccess = QUOTE([ARR_3(_medic, _patient, _bodyPart)] call FUNC(fractureSelect));
    };
    class ClosedReduction: CheckFracture {
        displayName = CSTRING(fracture_closed);
        displayNameProgress = CSTRING(perform);
        category = "surgery";
        treatmentLocations = QGVAR(closedLocation);
        allowedSelections[] = {"LeftArm", "RightArm", "LeftLeg", "RightLeg"};
        allowSelfTreatment = 0;
        medicRequired = QGVAR(closedReduction_MedLevel);
        treatmentTime = QGVAR(closedTime);
        items[] = {};
        condition = QUOTE([ARR_4(_medic, _patient, _bodyPart, 1)] call FUNC(fractureCheck));
        callbackSuccess = QUOTE([ARR_3(_medic, _patient, _bodyPart)] call FUNC(closedFracture));
    };
    class OpenReduction: CheckFracture {
        displayName = CSTRING(fracture_open);
        displayNameProgress = CSTRING(perform);
        category = "surgery";
        treatmentLocations = QGVAR(surgicalLocation);
        allowedSelections[] = {"LeftArm", "RightArm", "LeftLeg", "RightLeg"};
        allowSelfTreatment = 0;
        medicRequired = QGVAR(surgicalAction_MedLevel);
        treatmentTime = QGVAR(openTime);
        items[] = {"kat_plate"};
        consumeItem = 1;
        condition = QUOTE([ARR_4(_medic, _patient, _bodyPart, 3.5)] call FUNC(openFractureCheck));
        callbackSuccess = QUOTE([ARR_3(_medic, _patient, _bodyPart)] call FUNC(openFracture));
    };
    class Expose: BasicBandage {
        displayName = CSTRING(Retractor_Use);
        displayNameProgress = CSTRING(Retractor_Action);
        category = "surgery";
        treatmentLocations = QGVAR(surgicalLocation);
        allowedSelections[] = {"LeftArm", "RightArm", "LeftLeg", "RightLeg"};
        allowSelfTreatment = 0;
        medicRequired = QGVAR(surgicalAction_MedLevel);
        treatmentTime = QGVAR(intermediateTime);
        items[] = {"kat_retractor"};
        condition = QUOTE([ARR_4(_medic, _patient, _bodyPart, 2.1)] call FUNC(openFractureCheck));
        consumeItem = 0;
        callbackSuccess = QUOTE([ARR_4(_medic, _patient, _bodyPart, 2.1)] call FUNC(openFractureProgress));
    };
    class Incision: BasicBandage {
        displayName = CSTRING(Scalpel_Use);
        displayNameProgress = CSTRING(perform);
        category = "surgery";
        treatmentLocations = QGVAR(surgicalLocation);
        allowedSelections[] = {"LeftArm", "RightArm", "LeftLeg", "RightLeg"};
        allowSelfTreatment = 0;
        medicRequired = QGVAR(surgicalAction_MedLevel);
        treatmentTime = QGVAR(incisionTime);
        items[] = {"kat_scalpel"};
        condition = QUOTE([ARR_4(_medic, _patient, _bodyPart, 5)] call FUNC(openFractureCheck));
        callbackSuccess = QUOTE([ARR_3(_medic, _patient, _bodyPart)] call FUNC(openFractureIncision));
    };
    class Clamp: BasicBandage {
        displayName = CSTRING(Clamp_Use);
        displayNameProgress = CSTRING(Clamp_Action);
        category = "surgery";
        treatmentLocations = QGVAR(surgicalLocation);
        allowedSelections[] = {"LeftArm", "RightArm", "LeftLeg", "RightLeg"};
        allowSelfTreatment = 0;
        medicRequired = QGVAR(surgicalAction_MedLevel);
        treatmentTime = QGVAR(intermediateTime);
        items[] = {"kat_clamp"};
        condition = QUOTE([ARR_4(_medic, _patient, _bodyPart, 3.3)] call FUNC(openFractureCheck));
        consumeItem = 0;
        callbackSuccess = QUOTE([ARR_4(_medic, _patient, _bodyPart, 3.3)] call FUNC(openFractureProgress));
    };
    class Irrigate: BasicBandage {
        displayName = CSTRING(Irrigate_Use);
        displayNameProgress = CSTRING(Irrigate_Action);
        category = "surgery";
        treatmentLocations = QGVAR(surgicalLocation);
        allowedSelections[] = {"LeftArm", "RightArm", "LeftLeg", "RightLeg"};
        allowSelfTreatment = 0;
        medicRequired = QGVAR(surgicalAction_MedLevel);
        treatmentTime = QGVAR(intermediateTime);
        items[] = {"ACE_salineIV_250"};
        condition = QUOTE([ARR_4(_medic, _patient, _bodyPart, 2.3)] call FUNC(openFractureCheck));
        callbackSuccess = QUOTE([ARR_4(_medic, _patient, _bodyPart, 2.3)] call FUNC(openFractureProgress));
    };
    class Debridement: BasicBandage {
        displayName = CSTRING(Debride_Use);
        displayNameProgress = CSTRING(Debride_Action);
        category = "surgery";
        treatmentLocations = QGVAR(surgicalLocation);
        allowedSelections[] = {"Head", "Body", "LeftArm", "RightArm", "LeftLeg", "RightLeg"};
        allowSelfTreatment = 0;
        medicRequired = QGVAR(surgicalAction_MedLevel);
        treatmentTime = QGVAR(debrideTime);
        items[] = {"kat_scalpel"};
        condition = QUOTE([ARR_3(_medic, _patient, _bodyPart)] call FUNC(debridementCheck));
        consumeItem = 0;
        callbackSuccess = QUOTE([ARR_3(_medic, _patient, _bodyPart)] call FUNC(debridementClear));
    };
    class NPWT: BasicBandage {
        displayName = CSTRING(Vacuum_Use);
        displayNameProgress = CSTRING(Vacuum_Action);
        category = "surgery";
        treatmentLocations = QGVAR(surgicalLocation);
        allowedSelections[] = {"Head", "Body", "LeftArm", "RightArm", "LeftLeg", "RightLeg"};
        allowSelfTreatment = 0;
        medicRequired = QGVAR(surgicalAction_MedLevel);
        treatmentTime = QGVAR(npwtTime);
        items[] = {"kat_vacuum"};
        condition = QUOTE([ARR_3(_medic, _patient, _bodyPart)] call FUNC(debridementCheck));
        consumeItem = 0;
        callbackStart = QUOTE([ARR_2(_medic, _patient)] call FUNC(debridementStart));
        callbackSuccess = QUOTE([ARR_3(_medic, _patient, _bodyPart)] call FUNC(debridementMinor));
    };
};
