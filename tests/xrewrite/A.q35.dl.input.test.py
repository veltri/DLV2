input = """
% Total TBox Axioms: 121

notHearingDisability(X) :- SpeechDisability(X).
aux_0(X,Y) :- TalkingReading(X).
aux_1(X,Y) :- Little_or_No_Speech(X).
notDevice(X) :- Disability(X).
notHearingDisability(X) :- PhysicalDisability(X).
VisualDisability(X) :- Blind(X).
aux_2(X,Y) :- PhysicalDisability(X).
Device(X) :- AssistiveDevice(X).
TactileReading(X) :- BrailleWatch(X).
Communication_Device(X) :- ListenDevice(X).
Disability(X) :- MentalDisability(X).
aux_3(X,Y) :- BrailleWritingDevice(X).
SpeechDisability(X) :- Stuttering(X).
notAbility(X) :- Disability(X).
HearingAbility(X) :- Hear_partially(X).
Communication_Device(X) :- SpeechDevice(X).
PhysicalDisability(X) :- Paraplegia(X).
aux_4(X,Y) :- ListenDevice(X).
VisualDisability(X) :- LowVision(X).
aux_5(X,Y) :- Wheelchair(X).
Foldable_Wheelchair(X) :- LightweightFoldable_Wheelchair(X).
SensoryAbility(X) :- SightAbility(X).
aux_6(X,Y) :- FaceToFaceCommunicationDevice(X).
aux_7(X,Y) :- Disability(X).
notManual_Wheelchair(X) :- Motorised_Wheelchair(X).
PhysicalDisability(X) :- Muscular_dystrophy(X).
AssistiveDevice(X) :- Communication_Device(X).
TalkingReading(X) :- Talking_Thermometer(X).
Disability(X) :- HearingDisability(X).
aux_8(X,Y) :- Motorised_Wheelchair(X).
FaceToFaceCommunicationDevice(X) :- FaceToFaceCommunicationSoftware(X).
MentalDisability(X) :- Autism(X).
Disability(X) :- VisualDisability(X).
isAssistedBy(X, Y) :- assistsWith(Y, X).
assistsWith(Y, X) :- isAssistedBy(X, Y).
Ability(X) :- SpeechAbility(X).
aux_9(X,Y) :- TactileReading(X).
aux_10(X,Y) :- SpeechDevice(X).
ReadingDevice(X) :- TalkingReading(X).
notSpeechDisability(X) :- VisualDisability(X).
SightAbility(X) :- See(X).
MobilityDevice(X) :- Wheelchair(X).
Wheelchair(X) :- Motorised_Wheelchair(X).
SpeechDisability(X) :- Little_or_No_Speech(X).
SpeechDevice(X) :- TelephoneAid(X).
PhysicalDisability(X) :- Spina_Bifida(X).
Communication_Device(X) :- FaceToFaceCommunicationDevice(X).
aux_11(X,Y) :- Ability(X).
HearingDisability(X) :- Hard_of_hearing(X).
SensoryAbility(X) :- TactileAbility(X).
notCommunication_Device(X) :- MobilityDevice(X).
notAbility(X) :- Device(X).
aux_12(X,Y) :- Manual_Wheelchair(X).
LimbMobility(X) :- UpperLimbMobility(X).
notHearingDisability(X) :- VisualDisability(X).
TactileReading(X) :- BraillePillOrganiser(X).
aux_13(X,Y) :- Manual_Wheelchair(X).
Ability(X) :- PhysicalAbility(X).
PhysicalDisability(X) :- Multiple_sclerosis(X).
HearingDisability(X) :- Deaf(X).
Communication_Device(X) :- WritingDevice(X).
Disability(X) :- PhysicalDisability(X).
aux_14(X,Y) :- MobilityDevice(X).
affects(X, Y) :- isAffectedBy(Y, X).
isAffectedBy(Y, X) :- affects(X, Y).
aux_15(X,Y) :- Motorised_Wheelchair(X).
Manual_Wheelchair(X) :- Lightweight_Wheelchair(X).
MovementAbility(X) :- Reach(X).
HearingDisability(X) :- Deafened(X).
FaceToFaceCommunicationDevice(X) :- SymbolBoard(X).
SensoryAbility(X) :- HearingAbility(X).
Disability(X) :- SpeechDisability(X).
aux_16(X,Y) :- Paraplegia(X).
PhysicalDisability(X) :- Kyphosis(X).
MovementAbility(X) :- LimbMobility(X).
notMentalDisability(X) :- SpeechDisability(X).
PhysicalDisability(X) :- Osteogensis_Imperfecta(X).
Communication_Device(X) :- ReadingDevice(X).
Manual_Wheelchair(X) :- Foldable_Wheelchair(X).
PhysicalDisability(X) :- Hemiplegia(X).
aux_17(X,Y) :- Quadriplegia(X).
aux_18(X,Y) :- HearingDisability(X).
SightAbility(X) :- See_partially(X).
PhysicalDisability(X) :- Poliomyelitis(X).
PhysicalDisability(X) :- Amputation(X).
PhysicalDisability(X) :- Dystonia(X).
PhysicalDisability(X) :- Quadriplegia(X).
PhysicalDisability(X) :- Achondroplasia(X).
notSensoryAbility(X) :- SpeechAbility(X).
notPhysicalAbility(X) :- SensoryAbility(X).
Ability(X) :- SensoryAbility(X).
ReadingDevice(X) :- TactileReading(X).
notPhysicalDisability(X) :- SpeechDisability(X).
WritingDevice(X) :- BrailleWritingDevice(X).
PhysicalDisability(X) :- Guillaume_Barre(X).
PhysicalDisability(X) :- Scoliosis(X).
notLowerLimbMobility(X) :- UpperLimbMobility(X).
PhysicalDisability(X) :- Cerebral_palsy(X).
aux_19(X,Y) :- AssistiveDevice(X).
aux_20(X,Y) :- ReadingDevice(X).
aux_21(X,Y) :- TactileReading(X).
notMentalDisability(X) :- VisualDisability(X).
HearingAbility(X) :- Hear(X).
LimbMobility(X) :- LowerLimbMobility(X).
notPhysicalAbility(X) :- SpeechAbility(X).
aux_22(X,Y) :- Ability(X).
aux_23(X,Y) :- TalkingReading(X).
notMentalDisability(X) :- PhysicalDisability(X).
aux_24(X,Y) :- Deaf(X).
Wheelchair(X) :- Manual_Wheelchair(X).
Motorised_Wheelchair(X) :- BatteryPowered_Wheelchair(X).
MentalDisability(X) :- Epilepsy(X).
notPhysicalDisability(X) :- VisualDisability(X).
TactileReading(X) :- BrailleAlarmClock(X).
AssistiveDevice(X) :- MobilityDevice(X).
notHearingDisability(X) :- MentalDisability(X).
Lightweight_Wheelchair(X) :- LightweightFoldable_Wheelchair(X).
MentalDisability(X) :- IntellectualDisability(X).
aux_25(X,Y) :- Quadriplegia(X).
ListenDevice(X) :- TelephoneAid(X).
PhysicalAbility(X) :- MovementAbility(X).
isAssistedBy(X,Y) :- aux_11(X,Y).
Device(Y) :- aux_11(X,Y).
assistsWith(X,Y) :- aux_10(X,Y).
SpeechAbility(Y) :- aux_10(X,Y).
requiresAbility(X,Y) :- aux_13(X,Y).
UpperLimbMobility(Y) :- aux_13(X,Y).
assistsWith(X,Y) :- aux_12(X,Y).
LowerLimbMobility(Y) :- aux_12(X,Y).
assistsWith(X,Y) :- aux_15(X,Y).
LowerLimbMobility(Y) :- aux_15(X,Y).
assistsWith(X,Y) :- aux_14(X,Y).
MovementAbility(Y) :- aux_14(X,Y).
affects(X,Y) :- aux_1(X,Y).
SpeechAbility(Y) :- aux_1(X,Y).
affects(X,Y) :- aux_2(X,Y).
PhysicalAbility(Y) :- aux_2(X,Y).
requiresAbility(X,Y) :- aux_0(X,Y).
HearingAbility(Y) :- aux_0(X,Y).
assistsWith(X,Y) :- aux_5(X,Y).
LimbMobility(Y) :- aux_5(X,Y).
assistsWith(X,Y) :- aux_6(X,Y).
SpeechAbility(Y) :- aux_6(X,Y).
assistsWith(X,Y) :- aux_3(X,Y).
SightAbility(Y) :- aux_3(X,Y).
assistsWith(X,Y) :- aux_4(X,Y).
HearingAbility(Y) :- aux_4(X,Y).
assistsWith(X,Y) :- aux_9(X,Y).
SightAbility(Y) :- aux_9(X,Y).
affects(X,Y) :- aux_7(X,Y).
Ability(Y) :- aux_7(X,Y).
assistsWith(X,Y) :- aux_8(X,Y).
UpperLimbMobility(Y) :- aux_8(X,Y).
affects(X,Y) :- aux_25(X,Y).
LowerLimbMobility(Y) :- aux_25(X,Y).
assistsWith(X,Y) :- aux_23(X,Y).
SightAbility(Y) :- aux_23(X,Y).
affects(X,Y) :- aux_24(X,Y).
SpeechAbility(Y) :- aux_24(X,Y).
requiresAbility(X,Y) :- aux_21(X,Y).
TactileAbility(Y) :- aux_21(X,Y).
isAffectedBy(X,Y) :- aux_22(X,Y).
Disability(Y) :- aux_22(X,Y).
assistsWith(X,Y) :- aux_20(X,Y).
SightAbility(Y) :- aux_20(X,Y).
assistsWith(X,Y) :- aux_19(X,Y).
Ability(Y) :- aux_19(X,Y).
affects(X,Y) :- aux_18(X,Y).
HearingAbility(Y) :- aux_18(X,Y).
affects(X,Y) :- aux_17(X,Y).
UpperLimbMobility(Y) :- aux_17(X,Y).
affects(X,Y) :- aux_16(X,Y).
LowerLimbMobility(Y) :- aux_16(X,Y).
Q35(A) :- isAssistedBy(B,A), SpeechAbility(B).
Q35(A)?
"""
output = """
#rewriting: 7
"""
