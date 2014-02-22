enemyShotSpeed = 50;
local targetDistance = CurrentAI:GetTargetDistance():GetNormalize();
if(toPlayer == true)
then
	CurrentAI:Move(targetDistance);
else
	CurrentAI:Move(targetDistance*-1);
end

if(true)
then
	local enemyTime = 1;
	if(CurrentAI:GetLastShotTime() > enemyTime)
	then
		CurrentAI:Shoot(enemyShotSpeed);
	end
end