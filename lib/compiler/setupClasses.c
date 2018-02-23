// Do not modify this file, it is auto-generated
 
// includes
#include <CameraTriggerEntity.h>
#include <CustomCameraEffectManager.h>
#include <CustomCameraMovementManager.h>
#include <EventManager.h>
#include <GUISprite.h>
#include <HbiasMaskMBgmapSprite.h>
#include <ProgressManager.h>
#include <Hero.h>
#include <HeroIdle.h>
#include <HeroMoving.h>
#include <HeroState.h>
#include <MovingEntity.h>
#include <Collision.h>
#include <Door.h>
#include <GoalDoor.h>
#include <KeyDoor.h>
#include <LayerSwitchDoor.h>
#include <Gui.h>
#include <Collectable.h>
#include <Item.h>
#include <AutoPauseScreenState.h>
#include <LevelDoneScreenState.h>
#include <OptionsScreenState.h>
#include <PauseScreenState.h>
#include <PlatformerLevelState.h>
#include <AdjustmentScreenState.h>
#include <AutoPauseSelectScreenState.h>
#include <LangSelectScreenState.h>
#include <PrecautionScreenState.h>
#include <SplashScreenState.h>
#include <TitleScreenState.h>
#include <Clock.h>
#include <ClockManager.h>
#include <Error.h>
#include <FrameRate.h>
#include <I18n.h>
#include <MemoryPool.h>
#include <MessageDispatcher.h>
#include <Object.h>
#include <State.h>
#include <StateMachine.h>
#include <Telegram.h>
#include <VirtualList.h>
#include <VirtualNode.h>
#include <Camera.h>
#include <CameraEffectManager.h>
#include <CameraMovementManager.h>
#include <Game.h>
#include <Printing.h>
#include <AnimationController.h>
#include <AnimationCoordinator.h>
#include <AnimationCoordinatorFactory.h>
#include <BgmapAnimatedSprite.h>
#include <BgmapAnimationCoordinator.h>
#include <BgmapSprite.h>
#include <MBgmapSprite.h>
#include <ParamTableManager.h>
#include <ObjectAnimatedSprite.h>
#include <ObjectAnimationCoordinator.h>
#include <ObjectSprite.h>
#include <ObjectSpriteContainer.h>
#include <ObjectSpriteContainerManager.h>
#include <Sprite.h>
#include <SpriteManager.h>
#include <BgmapTexture.h>
#include <BgmapTextureManager.h>
#include <CharSet.h>
#include <CharSetManager.h>
#include <ObjectTexture.h>
#include <Texture.h>
#include <DirectDraw.h>
#include <Polyhedron.h>
#include <Sphere.h>
#include <Wireframe.h>
#include <WireframeManager.h>
#include <HardwareManager.h>
#include <KeypadManager.h>
#include <SoundManager.h>
#include <SRAMManager.h>
#include <TimerManager.h>
#include <VIPManager.h>
#include <Ball.h>
#include <Body.h>
#include <Box.h>
#include <CollisionHelper.h>
#include <CollisionManager.h>
#include <InverseBox.h>
#include <PhysicalWorld.h>
#include <Shape.h>
#include <Actor.h>
#include <AnimatedEntity.h>
#include <Container.h>
#include <Entity.h>
#include <EntityFactory.h>
#include <ManagedEntity.h>
#include <Particle.h>
#include <ParticleBody.h>
#include <ParticleRemover.h>
#include <ParticleSystem.h>
#include <SolidParticle.h>
#include <ReflectiveEntity.h>
#include <SpatialObject.h>
#include <Stage.h>
#include <UiContainer.h>
#include <AnimationInspectorState.h>
#include <DebugState.h>
#include <GameState.h>
#include <StageEditorState.h>
#include <AnimationInspector.h>
#include <Debug.h>
#include <OptionsSelector.h>
#include <StageEditor.h>
 
// setup function
void setupClasses(void)
{
	CameraTriggerEntity_setVTable();
	CustomCameraEffectManager_setVTable();
	CustomCameraMovementManager_setVTable();
	EventManager_setVTable();
	GUISprite_setVTable();
	HbiasMaskMBgmapSprite_setVTable();
	ProgressManager_setVTable();
	Hero_setVTable();
	HeroIdle_setVTable();
	HeroMoving_setVTable();
	HeroState_setVTable();
	MovingEntity_setVTable();
	Collision_setVTable();
	Door_setVTable();
	GoalDoor_setVTable();
	KeyDoor_setVTable();
	LayerSwitchDoor_setVTable();
	Gui_setVTable();
	Collectable_setVTable();
	Item_setVTable();
	AutoPauseScreenState_setVTable();
	LevelDoneScreenState_setVTable();
	OptionsScreenState_setVTable();
	PauseScreenState_setVTable();
	PlatformerLevelState_setVTable();
	AdjustmentScreenState_setVTable();
	AutoPauseSelectScreenState_setVTable();
	LangSelectScreenState_setVTable();
	PrecautionScreenState_setVTable();
	SplashScreenState_setVTable();
	TitleScreenState_setVTable();
	Clock_setVTable();
	ClockManager_setVTable();
	Error_setVTable();
	FrameRate_setVTable();
	I18n_setVTable();
	MemoryPool_setVTable();
	MessageDispatcher_setVTable();
	Object_setVTable();
	State_setVTable();
	StateMachine_setVTable();
	Telegram_setVTable();
	VirtualList_setVTable();
	VirtualNode_setVTable();
	Camera_setVTable();
	CameraEffectManager_setVTable();
	CameraMovementManager_setVTable();
	Game_setVTable();
	Printing_setVTable();
	AnimationController_setVTable();
	AnimationCoordinator_setVTable();
	AnimationCoordinatorFactory_setVTable();
	BgmapAnimatedSprite_setVTable();
	BgmapAnimationCoordinator_setVTable();
	BgmapSprite_setVTable();
	MBgmapSprite_setVTable();
	ParamTableManager_setVTable();
	ObjectAnimatedSprite_setVTable();
	ObjectAnimationCoordinator_setVTable();
	ObjectSprite_setVTable();
	ObjectSpriteContainer_setVTable();
	ObjectSpriteContainerManager_setVTable();
	Sprite_setVTable();
	SpriteManager_setVTable();
	BgmapTexture_setVTable();
	BgmapTextureManager_setVTable();
	CharSet_setVTable();
	CharSetManager_setVTable();
	ObjectTexture_setVTable();
	Texture_setVTable();
	DirectDraw_setVTable();
	Polyhedron_setVTable();
	Sphere_setVTable();
	Wireframe_setVTable();
	WireframeManager_setVTable();
	HardwareManager_setVTable();
	KeypadManager_setVTable();
	SoundManager_setVTable();
	SRAMManager_setVTable();
	TimerManager_setVTable();
	VIPManager_setVTable();
	Ball_setVTable();
	Body_setVTable();
	Box_setVTable();
	CollisionHelper_setVTable();
	CollisionManager_setVTable();
	InverseBox_setVTable();
	PhysicalWorld_setVTable();
	Shape_setVTable();
	Actor_setVTable();
	AnimatedEntity_setVTable();
	Container_setVTable();
	Entity_setVTable();
	EntityFactory_setVTable();
	ManagedEntity_setVTable();
	Particle_setVTable();
	ParticleBody_setVTable();
	ParticleRemover_setVTable();
	ParticleSystem_setVTable();
	SolidParticle_setVTable();
	ReflectiveEntity_setVTable();
	SpatialObject_setVTable();
	Stage_setVTable();
	UiContainer_setVTable();
	AnimationInspectorState_setVTable();
	DebugState_setVTable();
	GameState_setVTable();
	StageEditorState_setVTable();
	AnimationInspector_setVTable();
	Debug_setVTable();
	OptionsSelector_setVTable();
	StageEditor_setVTable();
}
