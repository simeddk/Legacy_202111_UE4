#include "CBTTaskNode_Speed.h"
#include "Global.h"
#include "Characters/CAIController.h"
#include "Characters/CEnemy_AI.h"

UCBTTaskNode_Speed::UCBTTaskNode_Speed()
{
	NodeName = "Speed";
}

EBTNodeResult::Type UCBTTaskNode_Speed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	ACAIController* cotroller = Cast<ACAIController>(OwnerComp.GetOwner());
	ACEnemy_AI* aiPawn = Cast<ACEnemy_AI>(cotroller->GetPawn());

	UCStatusComponent* status = CHelpers::GetComponent<UCStatusComponent>(aiPawn);

	status->SetSpeed(Type);

	return EBTNodeResult::Succeeded;
}