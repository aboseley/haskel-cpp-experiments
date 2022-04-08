robot (name, attack, hp) message = message (name, attack, hp)
getRobotName a_robot = a_robot (\(n, _, _) -> n)
getRobotAttack a_robot = a_robot (\(_, a, _) -> a)
getRobotHp a_robot = a_robot (\(_, _, h) -> h)

setRobotName a_robot n' = a_robot (\(n, a, h) -> robot (n', a, h))
setRobotAttack a_robot a' = a_robot (\(n, a, h) -> robot (n, a', h))
setRobotHp a_robot h' = a_robot (\(n, a, h) -> robot (n, a, h'))

printRobot a_robot =
    a_robot (\(n, a, h) -> n ++ ", attack : " ++ show a ++ ", hp: " ++ show h)

damage a_robot dmg = a_robot
    (\(n, a, h) ->
        let new_hp     = h - dmg
            limited_hp = max new_hp 0
        in  robot (n, a, limited_hp)
    )

killerRobot = robot ("killer", 25, 200)

nicerRobot = setRobotName killerRobot "kitty"
gentlerRobot = setRobotAttack nicerRobot 1
strongRobot = setRobotHp nicerRobot 100

afterHit = damage killerRobot 400

attacks attacker defender = damage defender attack
  where
    attack = if getRobotHp attacker > 10 then getRobotAttack attacker else 0

gentleGiant = robot ("mr friendly", 10, 300)

woundedGiant = killerRobot `attacks` gentleGiant


